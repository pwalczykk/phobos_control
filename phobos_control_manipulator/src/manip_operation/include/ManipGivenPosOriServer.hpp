#ifndef MANIPGIVENPOSORISERVER_HPP
#define MANIPGIVENPOSORISERVER_HPP

#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <rover_manip_control/PositionOrientation.h>


class ManipGivenPosOriServer
{

	 float x_given, y_given, z_given, angle_given, roll_given, grip_given;
	 float linear_increment;
	 float angular_increment;
	 bool active;
	 char character;
	 
	 rover_manip_control::PositionOrientation msgpub;
	 
	 ros::NodeHandle* nh;
	 ros::Publisher pub;
	 
	 public:
	 
	 ManipGivenPosOriServer(){};
	 ManipGivenPosOriServer(const char* topicpub, ros::NodeHandle* nh);
	 
	 void Init(const char* topicpub, ros::NodeHandle* nh);
	 void Publish();
	 void SetGivenValues(std::vector<float>* data);
	 void SetGivenValues(float x_to_set, float y_to_set, float z_to_set, float angle_to_set,float roll_given_to_set,float grip_given_to_set);
	 std::vector<float>* GetGivenValues(void);
	 void ProcessInput(void);
	 void Activate(void);
	 void Deactivate(void);
	 char Character(void);
	 void SetChar(char data);
	 void SetLinearIncrement(float data);
	 void SetAngularIncrement(float data);
	 
 };
#endif
