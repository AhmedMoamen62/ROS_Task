#include "Visualizer.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "lider_viewer_2");
  Visualizer lidar_visualizer("Lider 2", "/lidar2/lidar2/points", 10);
  ros::spin();

  return 0;
}