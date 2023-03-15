FROM osrf/ros:noetic-desktop

RUN apt-get update && apt-get install -y \
      libpcl-dev \
      ros-${ROS_DISTRO}-pcl-conversions \
      ros-${ROS_DISTRO}-pcl-ros && \
    rm -rf /var/lib/apt/lists/*

RUN echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc

COPY /catkin_ws /catkin_ws

RUN echo "source /catkin_ws/devel/setup.bash" >> ~/.bashrc