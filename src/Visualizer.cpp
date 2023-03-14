#include "Visualizer.h"

Visualizer::Visualizer(const char* viewer_name, const char* topic_name, const uint32_t queue_size) : m_viewer(viewer_name)
{
    // subscribe to the topic
    m_sub = m_node.subscribe(topic_name, queue_size, &Visualizer::showPointCloudCallBack, this);
    // initialize the timer
    m_timer = m_node.createTimer(ros::Duration(0.1), &Visualizer::timerCallBack, this);
}

void Visualizer::showPointCloudCallBack(const sensor_msgs::PointCloud2::ConstPtr& cloud)
{
    // convert ros PointCloud2 to pcl PointCloud and show it
    pcl::PointCloud<pcl::PointXYZI> pc;
    pcl::fromROSMsg(*cloud, pc);
    m_viewer.showCloud(pc.makeShared());
}

void Visualizer::timerCallBack(const ros::TimerEvent& event)
{
    // if the veiwer was stopped ('q' key pressed), shotdown the node
    if (m_viewer.wasStopped()) 
        ros::shutdown();
}