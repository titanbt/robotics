#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <stdio.h>
#include "std_msgs/String.h"

using namespace std;

int main(int argc, char** argv){
  ros::init(argc, argv, "pepper_publish");

  ros::NodeHandle node;
  tf::TransformListener listener;
  ros::Publisher chatter_pub = node.advertise<std_msgs::String>("chatter", 1000);	
  ros::Rate rate(50.0);

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

    if(left_hand_1_y > 0 && right_hand_1_y < 0 ) {
	ss << "a";
	msg.data = ss.str();
	cout <<"a"<<endl;
	chatter_pub.publish(msg); 
    }
   else if(right_hand_1_y > 0 && left_hand_1_y < 0) {
	ss << "d";
	msg.data = ss.str();
	cout <<"d"<<endl;
	chatter_pub.publish(msg); 
    }

    rate.sleep();
    }
  return 0;
}
