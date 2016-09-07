#include "../include/WheelJoyOp.hpp"

void WheelJoyOp::Init(const char* topicpub, ros::NodeHandle* nh){

	pub = nh->advertise<phobos_shared::TeleopWheelsFloat>(topicpub,100);

}

void WheelJoyOp::Publish(){

	msg.wheels_left = left_wheels_vel;
	msg.wheels_right = right_wheels_vel;

	pub.publish(msg);

}

void WheelJoyOp::ProcessInput(std::vector<float>* axes, std::vector<int>* buttons){

	this->left_wheels_vel = (*axes)[1] * joystick_sensitivity - (*axes)[0] * joystick_sensitivity;
	this->right_wheels_vel = (*axes)[1] * joystick_sensitivity + (*axes)[0] * joystick_sensitivity;

	if(left_wheels_vel > 1) left_wheels_vel = 1;
	if(left_wheels_vel < -1) left_wheels_vel = -1;
	if(right_wheels_vel >1) right_wheels_vel = 1;
	if(right_wheels_vel < -1) right_wheels_vel = -1;

	Publish();
}

void WheelJoyOp::SetJoystickSensitivity(float data){

	joystick_sensitivity = data;

}
