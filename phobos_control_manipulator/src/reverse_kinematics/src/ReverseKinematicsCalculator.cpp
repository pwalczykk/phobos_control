#include "../include/ReverseKinematicsCalculator.hpp"
#include <math.h>
#include "ros/ros.h"

ReverseKinematicsCalculator::ReverseKinematicsCalculator(){
	
	SetLengths(0.05,0.5,0.25,0.25);
	
}

ReverseKinematicsCalculator::ReverseKinematicsCalculator(double l1, double l2, double l3, double l4){
	
	SetLengths(l1, l2, l3, l4);
	
}

void ReverseKinematicsCalculator::SetPositionOrientation(double msgx, double msgy, double msgz, double msgangle, float msgroll, float msggrip){
	
	x = msgx;
	y = msgy;
	z = msgz;
	angle = msgangle;
	roll = msgroll;
	grip = msggrip;
	
}

 int ReverseKinematicsCalculator::SetLengths(double length1, double length2, double length3, double length4){
	 
	 l1 = length1;
	 l2 = length2;
	 l3 = length3;
	 l4 = length4;
	 
 }
 
 float ReverseKinematicsCalculator::Roll(void){
	 return roll;
 }
 
 float ReverseKinematicsCalculator::Grip(void){
	 return grip;
 }
 
 double ReverseKinematicsCalculator::ReturnLink(int link_number){
	 
	 return link[link_number];
	 
 }
 
 void ReverseKinematicsCalculator::Init(const char* topic, ros::NodeHandle *nh){
	 
	 pub = nh->advertise<phobos_shared::TeleopArmFloat>(topic,100);
	 
 }
 
 void ReverseKinematicsCalculator::Publish(void){
	 
	 msg.link_0 = link[0];
	 msg.link_1 = link[1];
	 msg.link_2 = link[2];
	 msg.link_3 = link[3];
	 msg.link_4 = roll;
	 msg.grip = this->grip;
	 
	 pub.publish(msg);
	 
 }
 
int ReverseKinematicsCalculator::CalculateReverseKinematics(){
	
	
	//Variable declaration
	double xw, yw, m, n, mi = 0, ni = 0, lkwadrat; 
	
	//Resetting link values
	link[0] = 0;
	link[1] = 0;
	link[2] = 0;
	link[3] = 0;
	
	//Calculate link0 value
	link[0] = atan2(y,x);
	
	//Check for NaN
	if(link[0] != link[0]) return -1;
	
	//Calculate local coordinates
	m = sqrt( pow(x,2) + pow(y,2) );
	n = z - 0.05;
	
	//Calculate wrist coordinates
	xw = m - l4 * cos(angle);
	yw = n - l4 * sin(angle);
	
	//Calculate length of a point connecting wrist and local (0,0)
	lkwadrat = pow(xw,2) + pow(yw,2);
	
	//Calculate link2 value
	link[2] = acos( (pow(l2,2) + pow(l3,2) - lkwadrat ) / (2*l2*l3) );
	
	//Check for NaN
	if(link[2] != link[2]) return -1;

	//Calculate compounds of link1
	mi = acos( (pow(l2,2)-pow(l3,2)+lkwadrat) / (2*l2*sqrt(lkwadrat)) );
	ni = atan2(yw,xw);
	
	//Calculate link1
	link[1] = mi + ni;
	
	//Check for NaN
	if(link[1] != link[1]) return -1;
		
	//Calculate link3 value
	link[3] = angle-link[1]-(link[2]-3.14159265359);
	
	//Check for NaN
	if(link[3] != link[3]) return -1;
	
	//Adjust for the simulation joint axes
	link[1] -= 1.57079632679;
	link[1] *= -1;
	
	return 0;
	
}
 

 


