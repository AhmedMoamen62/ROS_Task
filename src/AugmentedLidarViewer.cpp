#include "Visualizer.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "augmented_ider_viewer_1");
  Visualizer lidar_visualizer("Augmented Lider", "augmented_lidar", 10);
  ros::spin();

  return 0;
}