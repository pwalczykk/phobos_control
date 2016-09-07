#include "../include/ManipGivenPosOriServerJoy.hpp"

void ManipGivenPosOriServerJoy::Init(const char* topicpub, ros::NodeHandle* nh){

	x_given = 0;
	y_given = 0;
	z_given = 0;
	angle_given = 0;
	rollgrip_mode = false;
	pub = nh->advertise<phobos_shared::PositionOrientation>(topicpub,100);

}

void ManipGivenPosOriServerJoy::Publish(){

	msgpub.x = x_given;
	msgpub.y = y_given;
	msgpub.z = z_given;
	msgpub.angle = angle_given;
	msgpub.roll = roll_given;
	msgpub.grip = grip_given;

	pub.publish(msgpub);

}

void ManipGivenPosOriServerJoy::SetGivenValues(std::vector<float>* data){

	x_given = (*data)[0];
	y_given = (*data)[1];
	z_given = (*data)[2];
	angle_given = (*data)[3];
	roll_given = (*data)[4];
	grip_given = (*data)[5];

}

void ManipGivenPosOriServerJoy::SetGivenValues(float x_to_set, float y_to_set, float z_to_set, float angle_to_set,float roll_given_to_set,float grip_given_to_set){

	x_given = x_to_set;
	y_given = y_to_set;
	z_given = z_to_set;
	angle_given = angle_to_set;
	roll_given = roll_given_to_set;
	grip_given = grip_given_to_set;

}

std::vector<float>* ManipGivenPosOriServerJoy::GetGivenValues(void){

	static std::vector<float> GivenValues(6);
	GivenValues[0] = x_given;
	GivenValues[1] = y_given;
	GivenValues[2] = z_given;
	GivenValues[3] = angle_given;
	GivenValues[4] = roll_given;
	GivenValues[5] = grip_given;

	return &GivenValues;

}

void ManipGivenPosOriServerJoy::ProcessInput(std::vector<float>* axes, std::vector<int>* buttons){

	if((*buttons)[0]) rollgrip_mode = false;
	if((*buttons)[1]) rollgrip_mode = true;

	if(!rollgrip_mode){

		this->x_given += (*axes)[1] * joystick_sensitivity;
		this->y_given += (*axes)[0] * joystick_sensitivity;
		this->z_given += (*axes)[3] * joystick_sensitivity;
		this->angle_given += (*axes)[2] * joystick_sensitivity;
	}

	else{

		this->roll_given += (*axes)[2] * joystick_sensitivity;
		this->grip_given += (*axes)[1] * joystick_sensitivity;
	}

	if(roll_given > 3.1415) roll_given = 3.1415;
	if(roll_given < -3.1415) roll_given = -3.1415;

	if(grip_given > 1) grip_given = 1;
	if(grip_given < 0) grip_given = 0;

	Publish();
}

void ManipGivenPosOriServerJoy::SetJoystickSensitivity(float data){

	joystick_sensitivity = data;

}
