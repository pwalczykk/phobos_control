#include <ros/ros.h>
#include "../include/ManipGivenPosOriServer.hpp"
#include "../include/ManipGivenPosOriServerJoy.hpp"

#include <sensor_msgs/Joy.h>
#include <keyboard/Key.h>

#include <dynamic_reconfigure/server.h>
#include <phobos_control_manipulator/ManipParametersConfig.h>

ManipGivenPosOriServer keyboardop;
ManipGivenPosOriServerJoy joyop;

bool operatingKeyboard;
bool operatingJoy;
bool operatingGlobal;

std::vector<float> ax(6);
std::vector<int> but(12);

std::vector<float> LastGiven(6);

void RespondJoy(const sensor_msgs::Joy::ConstPtr& received){

	ax = received->axes;
	but = received->buttons;

}

void RespondDown(const keyboard::Key::ConstPtr& received){

	if(operatingKeyboard && operatingGlobal){
		ROS_INFO("Wlaczam Keyboard");
		keyboardop.Activate();
		keyboardop.SetChar(received->code);
	}

}

void RespondUp(const keyboard::Key::ConstPtr& received){

	if(operatingKeyboard && operatingGlobal){
		if(received->code == keyboardop.Character())
		ROS_INFO("Wylaczam keyboard");
			keyboardop.Deactivate();
	}

}

void ChangeOperation(phobos_control_manipulator::ManipParametersConfig &config, uint32_t level) {

	static int lastmethod;

	operatingGlobal = config.active;

	if(operatingGlobal){

	if(config.method != lastmethod){

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

}
}

  joyop.SetJoystickSensitivity(config.joystick_sensitivity);
  keyboardop.SetLinearIncrement(config.linear_increment);
  keyboardop.SetAngularIncrement(config.angular_increment);

  lastmethod = config.method;

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "rover_manip_operation_node");
	ros::NodeHandle nh;

	ros::Subscriber subkeydown, subkeyup, subjoy;
	ros::Rate looprate(10);


	//DYNAMIC RECONFIGURE
	dynamic_reconfigure::Server<phobos_control_manipulator::ManipParametersConfig> server;
	dynamic_reconfigure::Server<phobos_control_manipulator::ManipParametersConfig>::CallbackType f;

	f = boost::bind(&ChangeOperation, _1, _2);
	server.setCallback(f);


	//SUBSCIBERS
	subkeydown = nh.subscribe<keyboard::Key>("/control/keyboard/keydown", 100, RespondDown);
	subkeyup = nh.subscribe<keyboard::Key>("/control/keyboard/keyup", 100, RespondUp);
	subjoy = nh.subscribe<sensor_msgs::Joy>("/control/joystick/joy", 100, RespondJoy);


	//INIT OBJECTS
	keyboardop.Init("/control/reverse_kinematics/manip_given_position_orientation", &nh);
	keyboardop.SetGivenValues(0.25,0.0,0.0,-1.57,0,0);

	joyop.Init("/control/reverse_kinematics/manip_given_position_orientation", &nh);
	joyop.SetGivenValues(0.25,0.0,0.0,-1.57,0,0);

	while(ros::ok()){

		ros::spinOnce();

	if(operatingGlobal){

		if(operatingKeyboard){
			ROS_INFO("Dziala keyboard");
			keyboardop.ProcessInput();
		}

		if(operatingJoy){
			ROS_INFO("Dziala joy");
			joyop.ProcessInput(&ax,&but);
		}

	}

		looprate.sleep();

	}

	return 0;
}
