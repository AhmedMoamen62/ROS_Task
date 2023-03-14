#pragma once
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

/*
    This visualizer class is a helper class to visualize a point cloud from a specified topic
    and to shutdown the node when the user press 'q' key to close the window
*/

class Visualizer
{
    // visualizer instance
    pcl::visualization::CloudViewer m_viewer;
    // Node which is responsible for subscribing to the specified topic
    ros::NodeHandle m_node;
    // subscriber instance
    ros::Subscriber m_sub;
    // timer to periodically check the viewer state
    ros::Timer m_timer;   

    // timer call back function
    void timerCallBack(const ros::TimerEvent& event);
    // node call back function to visualize the point cloud
    void showPointCloudCallBack(const sensor_msgs::PointCloud2::ConstPtr& cloud);
    
public:
    // to initialize the point cloud merger you must provide the name of topic, the name of the viewer window and queue size for buffering 
    Visualizer(const char* viewer_name, const char* topic_name, const uint32_t queue_size);
};