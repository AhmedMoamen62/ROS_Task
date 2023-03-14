#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>

/*
    This point cloud merger class is resposible for synchronizing the point cloud data from 2 topics
    and merge them then publish the new augmented lidar to a new topic called 'augmented_lidar'
*/

class PointCloudMerger
{
    // here we're defining synchronization policy for 2 point cloud sensor msgs to be used for the synchronizer
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::PointCloud2, sensor_msgs::PointCloud2> MySyncPolicy;
    // here we're defining the synchronizer with the predefined policy
    typedef message_filters::Synchronizer<MySyncPolicy> Sync;

    // Node which is responsible for subscribing to 2 different topics, sync between them, merge both point clouds then publish the merged one
    ros::NodeHandle m_node;
    // augmented lidar publisher
    ros::Publisher m_lidar_pub;
    // 2 lidars subscribers
    message_filters::Subscriber<sensor_msgs::PointCloud2> m_lidar_1_sub, m_lidar_2_sub;
    // shared pointer of the synchronizer
    boost::shared_ptr<Sync> m_sync;

    // the merge point cloud call back function
    void mergePointCloudCallBack(const sensor_msgs::PointCloud2ConstPtr& input_1, const sensor_msgs::PointCloud2ConstPtr& input_2);

public:
    // to initialize the point cloud merger you must provide the name of 2 topics and queue size for buffering 
    PointCloudMerger(const char* topic1, const char* topic2, const uint32_t queue_size);
};