#ifndef MANIPGIVENPOSORISERVERJOY_HPP
#define MANIPGIVENPOSORISERVERJOY_HPP

#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <rover_manip_control/PositionOrientation.h>


class ManipGivenPosOriServerJoy
{

	 float x_given, y_given, z_given, angle_given, roll_given, grip_given, joystick_sensitivity;
	 bool rollgrip_mode;
	 
	 rover_manip_control::PositionOrientation msgpub;
	 
	 ros::NodeHandle* nh;
	 ros::Publisher pub;
	 
	 public:
	 
	 ManipGivenPosOriServerJoy(){};
	 ManipGivenPosOriServerJoy(const char* topicpub, ros::NodeHandle* nh);
	 
	 void Init(const char* topicpub, ros::NodeHandle* nh);
	 void Publish();
	 void SetGivenValues(std::vector<float>* data);
	 void SetGivenValues(float x_to_set, float y_to_set, float z_to_set, float angle_to_set,float roll_given_to_set,float grip_given_to_set);
	 std::vector<float>* GetGivenValues(void);
	 void ProcessInput(std::vector<float>* axes, std::vector<int>* buttons);
	 void SetJoystickSensitivity(float data);
	 
 };
#endif
