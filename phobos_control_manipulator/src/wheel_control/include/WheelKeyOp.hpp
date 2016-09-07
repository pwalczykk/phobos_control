#ifndef WheelKeyOp_HPP
#define WheelKeyOp_HPP

#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <phobos_shared/TeleopWheelsFloat.h>


class WheelKeyOp
{

	 float max_vel;
	 float turning_factor;
	 float left_wheels_vel, right_wheels_vel;
	 bool active, wset, sset, dset, aset;
	 
	 phobos_shared::TeleopWheelsFloat msg;
	 
	 ros::NodeHandle* nh;
	 ros::Publisher pub;
	 
	 public:
	 
	 WheelKeyOp(){};
	 WheelKeyOp(const char* topicpub, ros::NodeHandle* nh);
	 
	 void Init(const char* topicpub, ros::NodeHandle* nh);
	 void Publish();
	 void ProcessInput(void);
	 void Activate(void);
	 void Deactivate(void);
	 void SetChar(char data);
	 bool AllOff(void);
	 void ResetChar(char data);
	 void SetMaxVel(float data);
	 void SetTurningFactor(float data);
	 
 };
#endif
