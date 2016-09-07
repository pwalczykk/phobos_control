#include "../include/WheelKeyOp.hpp"

void WheelKeyOp::Init(const char* topicpub, ros::NodeHandle* nh){

	max_vel = 0.5;
	turning_factor = 0.5;
	active = false;

	pub = nh->advertise<phobos_shared::TeleopWheelsFloat>(topicpub,100);

}

void WheelKeyOp::Publish(){

	msg.wheels_left = left_wheels_vel;
	msg.wheels_right = right_wheels_vel;

	pub.publish(msg);

}

void WheelKeyOp::ProcessInput(void){

	left_wheels_vel = 0;
	right_wheels_vel = 0;

	if(active){

		if(wset){
			left_wheels_vel += max_vel;
			right_wheels_vel += max_vel;
		}
		if(sset){
			left_wheels_vel -= max_vel;
			right_wheels_vel -= max_vel;
		}
		if(aset){
			left_wheels_vel -= turning_factor*max_vel/2;
			right_wheels_vel += turning_factor*max_vel/2;
		}
		if(dset){
			left_wheels_vel += turning_factor*max_vel/2;
			right_wheels_vel -= turning_factor*max_vel/2;
		}

		if(left_wheels_vel > 1) left_wheels_vel = 1;
		if(left_wheels_vel < -1) left_wheels_vel = -1;
		if(right_wheels_vel > 1) right_wheels_vel = 1;
		if(right_wheels_vel < -1) right_wheels_vel = -1;

}

	Publish();

}


void WheelKeyOp::Activate(void){

	active = true;

}

void WheelKeyOp::Deactivate(void){

	active = false;

}

void WheelKeyOp::SetChar(char data){

	//printf("set: %c\n", data);

	if(data == 'w') wset = true;
	if(data == 's') sset = true;
	if(data == 'a') aset = true;
	if(data == 'd') dset = true;

}

void WheelKeyOp::ResetChar(char data){

	//printf("reset: %c\n", data);

	if(data == 'w') wset = false;
	if(data == 's') sset = false;
	if(data == 'a') aset = false;
	if(data == 'd') dset = false;

}

bool WheelKeyOp::AllOff(void){

	if(!wset && !sset && !aset && !dset) return 1;
	else return 0;

}

void WheelKeyOp::SetMaxVel(float data){
	max_vel = data;
}

void WheelKeyOp::SetTurningFactor(float data){
	turning_factor = data;
}
