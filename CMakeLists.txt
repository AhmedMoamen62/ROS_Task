cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)
project(combine_lidars)

find_package(catkin REQUIRED COMPONENTS message_filters roscpp sensor_msgs pcl_ros pcl_conversions)
find_package(PCL REQUIRED)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(MergerNode src/MergerNode.cpp src/PointCloudMerger.cpp)
target_link_libraries(MergerNode ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(LidarViewer1 src/LidarViewer1.cpp src/Visualizer.cpp)
target_link_libraries(LidarViewer1 ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(LidarViewer2 src/LidarViewer2.cpp src/Visualizer.cpp)
target_link_libraries(LidarViewer2 ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(AugmentedLidarViewer src/AugmentedLidarViewer.cpp src/Visualizer.cpp)
target_link_libraries(AugmentedLidarViewer ${catkin_LIBRARIES} ${PCL_LIBRARIES})