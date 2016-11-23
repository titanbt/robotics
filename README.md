# robotics

## Setup environments

##### 1. Create a project for kinect by using the following command:

```
$ cd %TOP_DIR_YOUR_CATKIN_WS%/src
$ catkin_create_pkg robot_setup_tf roscpp tf geometry_msgs
```

##### 2. Setup ROS for Arduino

  **http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup**

## Running

##### 1. Run Roscore

```
$ roscore
```
##### 2. Run Serial Port of Arduino

```
$ rosrun rosserial_python serial_node.py /dev/ttyACM0
```
##### 3. Run Kinect

```
$ rosrun openni_tracker openni_tracker
```
##### 4. Run Listener for Kinect

```
$ rosrun robot_setup_tf tf_listener
```
