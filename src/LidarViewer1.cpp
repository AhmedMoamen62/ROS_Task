#include "Visualizer.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "lider_viewer_1");
  Visualizer lidar_visualizer("Lider 1", "/lidar1/lidar1/points", 10);
  ros::spin();

  return 0;
}