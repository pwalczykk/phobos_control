#include "ros/ros.h"
#include "../include/ReverseKinematicsCalculator.hpp"
#include "phobos_shared/PositionOrientation.h"

float pi = 3.14159265359;

ReverseKinematicsCalculator cal;

void CalculateReverseKinematics(const phobos_shared::PositionOrientation::ConstPtr& msg)
{

  //ROS_INFO("Data received: [X = %f, Y = %f, Z = %f, angle = %f]", msg->x, msg->y, msg->z, msg->angle);

  cal.SetPositionOrientation(msg->x, msg->y, msg->z, msg->angle, msg->roll, msg->grip);

  if(cal.CalculateReverseKinematics()){
	  ROS_INFO("Error calculating inverse kinematics.");
	  /*
      ROS_INFO("Link0 = %f, Link1 = %f Link2 = %f Link3 = %f",cal.ReturnLink(0)*180/pi,cal.ReturnLink(1)*180/pi,cal.ReturnLink(2)*180/pi,cal.ReturnLink(3)*180/pi );
      ROS_INFO("Link0 = %f, Link1 = %f Link2 = %f Link3 = %f",cal.ReturnLink(0),cal.ReturnLink(1),cal.ReturnLink(2),cal.ReturnLink(3) );
	  */
  }

  else{

	 // ROS_INFO("Link0 = %f, Link1 = %f Link2 = %f Link3 = %f",cal.ReturnLink(0)*180/pi,cal.ReturnLink(1)*180/pi,cal.ReturnLink(2)*180/pi,cal.ReturnLink(3)*180/pi );
      //ROS_INFO("Link0 = %f, Link1 = %f Link2 = %f Link3 = %f",cal.ReturnLink(0),cal.ReturnLink(1),cal.ReturnLink(2),cal.ReturnLink(3) );

	cal.Publish();
  }



}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "phobos_shared_node");
  ros::NodeHandle nh;

  cal.SetLengths(0.05,0.5,0.25,0.25);
  cal.Init("/control/teleop/arm", &nh);

  ros::Subscriber sub = nh.subscribe("/control/reverse_kinematics/manip_given_position_orientation", 10, CalculateReverseKinematics);

  ros::spin();

  return 0;
}
