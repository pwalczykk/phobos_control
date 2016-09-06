#include "../include/ManipGivenPosOriServer.hpp"

void ManipGivenPosOriServer::Init(const char* topicpub, ros::NodeHandle* nh){
	
	x_given = 0;
	y_given = 0;
	z_given = 0;
	angle_given = 0;
	
	linear_increment = 0.01;
	angular_increment = 0.017453293;
	
	active = false;
	
	pub = nh->advertise<rover_manip_control::PositionOrientation>(topicpub,100);
	
}

void ManipGivenPosOriServer::Publish(){
	
	msgpub.x = x_given;
	msgpub.y = y_given;
	msgpub.z = z_given;
	msgpub.angle = angle_given;
	msgpub.roll = roll_given;
	msgpub.grip = grip_given;
	
	pub.publish(msgpub);

}

void ManipGivenPosOriServer::SetGivenValues(std::vector<float>* data){
	
	x_given = (*data)[0];
	y_given = (*data)[1];
	z_given = (*data)[2];
	angle_given = (*data)[3];
	roll_given = (*data)[4];
	grip_given = (*data)[4];
	
}

void ManipGivenPosOriServer::SetGivenValues(float x_to_set, float y_to_set, float z_to_set, float angle_to_set,float roll_given_to_set,float grip_given_to_set){
	
	x_given = x_to_set;
	y_given = y_to_set;
	z_given = z_to_set;
	angle_given = angle_to_set;
	roll_given = roll_given_to_set;
	grip_given = grip_given_to_set;
	
}

std::vector<float>* ManipGivenPosOriServer::GetGivenValues(void){
	
	static std::vector<float> GivenValues(6);
	GivenValues[0] = x_given;
	GivenValues[1] = y_given;
	GivenValues[2] = z_given;
	GivenValues[3] = angle_given;
	GivenValues[4] = roll_given;
	GivenValues[5] = grip_given;
	
	return &GivenValues;

}

void ManipGivenPosOriServer::ProcessInput(void){
	
	if(active){
	
	switch(character){
		
		case 'w':
		this->x_given += linear_increment;
		break;
		
		case 's':
		this->x_given -= linear_increment;
		break;
		
		case 'a':
		this->y_given -= linear_increment;
		break;
		
		case 'd':
		this->y_given += linear_increment;
		break;
		
		case 'r':
		this->z_given += linear_increment;
		break;
		
		case 'f':
		this->z_given -= linear_increment;
		break;
		
		case 'e':
		this->angle_given += angular_increment;
		break;
		
		case 'q':
		this->angle_given -= angular_increment;
		break;
		
		case 'o':
		this->roll_given += angular_increment;
		break;
		
		case 'p':
		this->roll_given -= angular_increment;
		break;
		
		case 'k':
		this->grip_given += linear_increment;
		break;
		
		case 'l':
		this->grip_given -= linear_increment;
		break;
		
	}
	
	Publish();
	
	}
	
}

void ManipGivenPosOriServer::Activate(void){
	
	active = true;
	
}

void ManipGivenPosOriServer::Deactivate(void){
	
	active = false;
	
}

char ManipGivenPosOriServer::Character(void){
	
	return character;
	
}

void ManipGivenPosOriServer::SetChar(char data){
	
	character = data;
	
}

void ManipGivenPosOriServer::SetLinearIncrement(float data){
	linear_increment = data;
}

void ManipGivenPosOriServer::SetAngularIncrement(float data){
	angular_increment = data;
}
