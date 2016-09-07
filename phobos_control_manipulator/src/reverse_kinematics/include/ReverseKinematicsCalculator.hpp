#ifndef REVERSEKINEMATICSCALCULATOR_HPP_
#define REVERSEKINEMATICSCALCULATOR_HPP_

#include <ros/ros.h>
#include <phobos_shared/TeleopArmFloat.h>

class ReverseKinematicsCalculator
{
    double x,y,z,angle,roll,grip;
	double link [4];
	double l1, l2, l3, l4;
	
	ros::NodeHandle *nh;
	ros::Publisher pub;
	phobos_shared::TeleopArmFloat msg;
	
	
public:

	ReverseKinematicsCalculator();
    ReverseKinematicsCalculator(double length1, double length2, double length3, double length4);
    ~ReverseKinematicsCalculator(){};
    
    void SetPositionOrientation(double msgx, double msgy, double msgz, double msgangle, float msgroll, float msggrip);
    int SetLengths(double length1, double length2, double length3, double length4);
	int CalculateReverseKinematics();
	void Init(const char* topic, ros::NodeHandle *nh);
	void Publish(void);
	float Roll(void);
	float Grip(void);
	double ReturnLink(int link_number);
	
};

#endif
