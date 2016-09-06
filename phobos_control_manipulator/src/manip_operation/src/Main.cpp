#include <ros/ros.h>
#include "../include/ManipGivenPosOriServer.hpp"
#include "../include/ManipGivenPosOriServerJoy.hpp"

#include <sensor_msgs/Joy.h>
#include <keyboard/Key.h>

#include <dynamic_reconfigure/server.h>
#include <manip_dynamic_server/ManipParametersConfig.h>

ManipGivenPosOriServer keyboardop;
ManipGivenPosOriServerJoy joyop;

bool operatingKeyboard;
bool operatingJoy;

std::vector<float> ax(7);
std::vector<int> but(12);

std::vector<float> LastGiven(6);

void RespondJoy(const sensor_msgs::Joy::ConstPtr& received){
	
	ax = received->axes;
	but = received->buttons;
	
}

void RespondDown(const keyboard::Key::ConstPtr& received){
	
	if(operatingKeyboard){
		keyboardop.Activate();
		keyboardop.SetChar(received->code);
	}
	
}

void RespondUp(const keyboard::Key::ConstPtr& received){
	
	if(operatingKeyboard){
		if(received->code == keyboardop.Character()) 
			keyboardop.Deactivate();
	}
	
}

void ChangeOperation(manip_dynamic_server::ManipParametersConfig &config, uint32_t level) {
	
  //TURNING KEYBOARD ON
  if(config.method == 1) {
	  LastGiven = *(joyop.GetGivenValues());
	  keyboardop.SetGivenValues(&LastGiven);
	  operatingKeyboard = true;
  }
  else{
	  operatingKeyboard = false;
  }
  
  //TURNING JOY ON
  if(config.method == 0) {
	  LastGiven = *(keyboardop.GetGivenValues());
	  joyop.SetGivenValues(&LastGiven);
	  operatingJoy = true;
  }
  else{
	  operatingJoy = false;
  }
  
  joyop.SetJoystickSensitivity(config.joystick_sensitivity);
  keyboardop.SetLinearIncrement(config.linear_increment);
  keyboardop.SetAngularIncrement(config.angular_increment);
  
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "rover_manip_operation_node");
	ros::NodeHandle nh;
	
	ros::Subscriber subkeydown, subkeyup, subjoy;
	ros::Rate looprate(10);
	
	
	//DYNAMIC RECONFIGURE
	dynamic_reconfigure::Server<manip_dynamic_server::ManipParametersConfig> server;
	dynamic_reconfigure::Server<manip_dynamic_server::ManipParametersConfig>::CallbackType f;

	f = boost::bind(&ChangeOperation, _1, _2);
	server.setCallback(f);
	
	
	//SUBSCIBERS
	subkeydown = nh.subscribe<keyboard::Key>("/control/keyboard/keydown", 100, RespondDown);
	subkeyup = nh.subscribe<keyboard::Key>("/control/keyboard/keyup", 100, RespondUp);
	subjoy = nh.subscribe<sensor_msgs::Joy>("/control/joystick/joy", 100, RespondJoy);
	
	
	//INIT OBJECTS
	keyboardop.Init("/control/manip_given_position_orientation", &nh);
	keyboardop.SetGivenValues(0.25,0.0,0.0,-1.57,0,0);
	
	joyop.Init("/control/manip_given_position_orientation", &nh);
	joyop.SetGivenValues(0.25,0.0,0.0,-1.57,0,0);
	
	while(ros::ok()){
		
		ros::spinOnce();
		
		if(operatingKeyboard){
			keyboardop.ProcessInput();
		}
		
		if(operatingJoy){
			joyop.ProcessInput(&ax,&but);
		}
		
		looprate.sleep();
		
	}
	
	return 0;
}
