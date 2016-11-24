#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <stdio.h>
#include "std_msgs/String.h"
#include <serial/serial.h>

using namespace std;

int main(int argc, char** argv){
  ros::init(argc, argv, "pepper_publish");

  ros::NodeHandle node;
  tf::TransformListener listener;
  ros::Publisher chatter_pub = node.advertise<std_msgs::String>("chatter", 1000);	
  ros::Rate rate(50.0);
  serial::Serial my_serial("/dev/ttyUSB0", 9600, serial::Timeout::simpleTimeout(1000));

  while (node.ok()){
    std_msgs::String msg;
    std::stringstream ss;
    tf::StampedTransform transform_left;
    tf::StampedTransform transform_right;
    
    try{
      listener.lookupTransform("/torso_1", "/left_hand_1", ros::Time(0), transform_left);  
    }
    catch (tf::TransformException ex){
         ROS_ERROR("%s",ex.what());
    }

    try{
      listener.lookupTransform("/torso_1", "/right_hand_1", ros::Time(0), transform_right);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
    }
    
    double left_hand_1_y = transform_left.getOrigin().y();
    double right_hand_1_y = transform_right.getOrigin().y();

    double right_hand_1_z = transform_right.getOrigin().z();
    double left_hand_1_z = transform_left.getOrigin().z();


    if(left_hand_1_y > 0 && right_hand_1_y < 0 ) {
      ss << "a";
      msg.data = ss.str();
      cout <<"a"<<endl;
      chatter_pub.publish(msg); 
      my_serial.write("a");
    }
    else if(right_hand_1_y > 0 && left_hand_1_y < 0) {
      ss << "d";
      msg.data = ss.str();
      cout <<"d"<<endl;
      chatter_pub.publish(msg); 
      my_serial.write("d");
    }
    else if(right_hand_1_y > 0 && left_hand_1_y > 0) {
      ss << "w";
      msg.data = ss.str();
      cout <<"w"<<endl;
      chatter_pub.publish(msg);
      my_serial.write("w");
    }
    else if(right_hand_1_z > 0.15) {
      ss << "s";
      msg.data = ss.str();
      cout <<"s"<<endl;
      chatter_pub.publish(msg);
      my_serial.write("s");
    }
    else if(left_hand_1_z > 0.15) {
      ss << "s";
      msg.data = ss.str();
      cout <<"s"<<endl;
      chatter_pub.publish(msg);
      my_serial.write("s");
    }
    else if(left_hand_1_y < 0 && right_hand_1_y < 0 ) {
      ss << "stop";
      msg.data = ss.str();
      cout <<"stop"<<endl;
      chatter_pub.publish(msg);
      my_serial.write("stop");
    }

    rate.sleep();
    }
  return 0;
}
