# robotics

## Setup environments

##### 1. Create a project for kinect by using the following command:

```
$ cd %TOP_DIR_YOUR_CATKIN_WS%/src
$ catkin_create_pkg robot_setup_tf roscpp tf geometry_msgs
```
In which:
  - **robot_setup_tf:** the name of project.
  - **roscpp tf geometry_msgs:** the name of library included into the project.

##### 2. Setup ROS for Arduino

  **http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup**

## Running without XBee

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
## Setup and Running with XBee

##### 1. Requirements
  - **XBee Explorer:** For connect XBee with computer (Sending data).
  - **XBee Shield:** For connect XBee with Arduino (Receiving data).
  - **Xbee (ZigBee):** Sending and Receiving Signal.
  - **XCTU Software:** Testing XBee working on computer.

##### 2. Setup ROS library for Serial Port (For writing data to XBee Explorer via port tyyUSB* - Baud 9600)

  **https://github.com/wjwwood/serial**

###### Note:
  1. Should Git Clone **Serial** folder into **catkin_ws/src** folder.
  2. Change directory in **Makefile** following ROS directory: 
  
  **CMAKE_FLAGS := -DCMAKE_INSTALL_PREFIX=/opt/ros/indigo** (Here ROS is installed in **opt** folder).
