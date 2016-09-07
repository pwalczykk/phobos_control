#ifndef WHEELJOYOP_HPP
#define WHEELJOYOP_HPP

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <phobos_shared/TeleopWheelsFloat.h>

class WheelJoyOp
{
	 
	 ros::NodeHandle* nh;
	 ros::Publisher pub;
	 
	 phobos_shared::TeleopWheelsFloat msg;
	 
	 float joystick_sensitivity, left_wheels_vel, right_wheels_vel;
	 
	 public:
	 
	 WheelJoyOp(){};
	 WheelJoyOp(const char* topicpub, ros::NodeHandle* nh);
	 
	 void Init(const char* topicpub, ros::NodeHandle* nh);
	 void Publish();
	 void ProcessInput(std::vector<float>* axes, std::vector<int>* buttons);
	 void SetJoystickSensitivity(float data);
	 
 };
#endif
