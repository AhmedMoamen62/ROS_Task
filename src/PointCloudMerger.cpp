#include "PointCloudMerger.h"

PointCloudMerger::PointCloudMerger(const char* topic1, const char* topic2, const uint32_t queue_size)
{
    // subscribe both lidars with their topics
    m_lidar_1_sub.subscribe(m_node, topic1, queue_size);
    m_lidar_2_sub.subscribe(m_node, topic2, queue_size);
    // advertise the augmeted lidar to a new topic called 'augmented_lidar'
    m_lidar_pub = m_node.advertise<sensor_msgs::PointCloud2>("augmented_lidar", queue_size);
    // reset the shared pointer with a new instance of the synchronizer
    m_sync.reset(new Sync(MySyncPolicy(queue_size), m_lidar_1_sub, m_lidar_2_sub));
    // register the callback function for the synchronizer
    m_sync->registerCallback(boost::bind(&PointCloudMerger::mergePointCloudCallBack, this, _1, _2));
}

void PointCloudMerger::mergePointCloudCallBack(const sensor_msgs::PointCloud2ConstPtr& input_1, const sensor_msgs::PointCloud2ConstPtr& input_2)
{
    ROS_INFO("Begin combining lidars");

    /*
        pc1: the first lidar data
        pc2: the second lidar data
        pc2_transformed: the second lidar data after taking shift and rotation into consideration
        pc_combined: the sum of pc1 and pc2_transformed
        pc_augmented: the lidar data pc_combined but after shifting it by +20 in x-direction
    */
    pcl::PointCloud<pcl::PointXYZI> pc1, pc2, pc2_transformed, pc_combined, pc_augmented;

    // convert ros PointCloud2 to pcl PointCloud
    pcl::fromROSMsg(*input_1, pc1);
    pcl::fromROSMsg(*input_2, pc2);

    // define the theta between the second lidar and the first one (-90 degree around the z-axis)
    float theta = -M_PI / 2;

    // define the transformation for second lidar
    Eigen::Affine3f transform_pc2 = Eigen::Affine3f::Identity();
    // reverse the +10 shift in the x-direction
    transform_pc2.translation() << -0.1, 0.0, 0.0;
    // define the rotation around z-axis
    transform_pc2.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
    // apply the tranformation
    pcl::transformPointCloud(pc2, pc2_transformed, transform_pc2);

    // combine both lidars after calibration
    pc_combined += pc1;
    pc_combined += pc2_transformed;

    // define new tranformation for the comined lidar
    Eigen::Affine3f transform_msg = Eigen::Affine3f::Identity();
    // add +20 shift in the x-direction
    transform_msg.translation() << 0.2, 0.0, 0.0;
    // apply the tranformation
    pcl::transformPointCloud(pc_combined, pc_augmented, transform_msg);

    // define the msg
    sensor_msgs::PointCloud2 msg;
    // convert pcl PointCloud to ros PointCloud2
    pcl::toROSMsg(pc_augmented, msg);
    // publish the message
    m_lidar_pub.publish(msg);

    ROS_INFO("End combining lidars");
}