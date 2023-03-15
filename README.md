# ROS_Task
This repo contains ros package to combine data from 2 lidars and it's based on ros1 noetic distro

The merged data is published to a topic called `augmented_lidar`

Here's a link for a [video demo](https://drive.google.com/file/d/1zrZsC_ODZdiBNM_z2taDyb1Z8lhEtoqc/view?usp=sharing)

## Run locally
To run the package locally you need to create your workspace then put this package 

### Dependencies
you will need to install the following dependencies

- pcl library
```
sudo apt install libpcl-dev
```

- pcl_ros package
```
sudo apt install ros-noestic-pcl-ros
```

- pcl_conversions package
```
sudo apt install ros-noestic-pcl-conversions
```

### Demo
after installing dependencies you're ready to build and run the demo

- build the package

```
catkin_make
```

- source the `setup.bash` file

```
source /${workspace_dir}/devel/setup.bash
```

- run master node

```
roscore
```

now you will need to run 3 viewers to view each point cloud
`Note:` you will need to zoom out to fit the point cloud

1- Lidar 1

```
rosrun combine_lidars LidarViewer1
```

2- Lidar 2

```
rosrun combine_lidars LidarViewer2
```

3- Augmented Lidar (output)

```
rosrun combine_lidars AugmentedLidarViewer
```

- run the merger node to merge both point clouds

```
rosrun combine_lidars MergerNode
```

- play the bag and see the output

```
rosbag play ${path_to_the_bag}
```

## Docker
Here we're providing a docker image to encapsulate all dependencies and the bag so you can run the bag nad merge both lidars data
`Note:` docker image can't run lidars view right now but you can listen to any topic outside the docker image by running the docker image with `--net=host`

To run the demo with docker you can use the following steps:

- pull the image

```
docker pull ahmedmoamen62/combine-lidars
```

- run the image

```
docker run -it --net=host combine-lidars
```

- run the master node inside the container

```
roscore
```

- open new terminal for the same running container so first you need to open a new terminal then run the following command

```
docker ps
```

- read the container id `${CONTAINER_ID}` then run the following command

```
docker exec -it ${CONTAINER_ID} bash
```

- run the merger node

```
rosrun combine-lidars MergerNode
```

- do the same steps to open new terminal for the same running container then run the following command to play the bag
```
rosbag play catkin_ws/lidar.bag
```

- optionally, you can run the viewers node