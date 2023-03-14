#include "PointCloudMerger.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "PointCloudMerger");
  PointCloudMerger pcMerger("/lidar1/lidar1/points", "/lidar2/lidar2/points", 10);
  ros::spin();

  return 0;
}