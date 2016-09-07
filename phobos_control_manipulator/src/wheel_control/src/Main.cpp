#include <ros/ros.h>
#include "../include/WheelKeyOp.hpp"
#include "../include/WheelJoyOp.hpp"

#include <sensor_msgs/Joy.h>
#include <keyboard/Key.h>

#include <dynamic_reconfigure/server.h>
#include <phobos_control_manipulator/WheelsParamConfig.h>

WheelKeyOp keyboardop;
WheelJoyOp joyop;

bool operatingKeyboard;
bool operatingJoy;
bool operatingGlobal;

std::vector<float> ax(7);
std::vector<int> but(12);


void RespondJoy(const sensor_msgs::Joy::ConstPtr& received){

	ax = received->axes;
	but = received->buttons;

}

void RespondDown(const keyboard::Key::ConstPtr& received){

	if(operatingKeyboard && operatingGlobal){

		keyboardop.Activate();
		keyboardop.SetChar(received->code);
	}

}

void RespondUp(const keyboard::Key::ConstPtr& received){

	if(operatingKeyboard && operatingGlobal){

		keyboardop.ResetChar(received->code);
			if(keyboardop.AllOff())
			keyboardop.Deactivate();
	}

}

void ChangeOperation(phobos_control_manipulator::WheelsParamConfig &config, uint32_t level) {

  //TURNING KEYBOARD ON
  if(config.method == 1) {
	  operatingKeyboard = true;
  }
  else{
	  operatingKeyboard = false;
  }

  //TURNING JOY ON
  if(config.method == 0) {
	  operatingJoy = true;
  }
  else{
	  operatingJoy = false;
  }

  joyop.SetJoystickSensitivity(config.max_velocity);
  keyboardop.SetMaxVel(config.max_velocity);
  keyboardop.SetTurningFactor(config.keyboard_turning);
  operatingGlobal = config.active;

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "wheel_control");
	ros::NodeHandle nh;

	ros::Subscriber subkeydown, subkeyup, subjoy;
	ros::Rate looprate(10);


	//DYNAMIC RECONFIGURE
	dynamic_reconfigure::Server<phobos_control_manipulator::WheelsParamConfig> server;
	dynamic_reconfigure::Server<phobos_control_manipulator::WheelsParamConfig>::CallbackType f;

	f = boost::bind(&ChangeOperation, _1, _2);
	server.setCallback(f);


	//SUBSCIBERS
	subkeydown = nh.subscribe<keyboard::Key>("/control/keyboard/keydown", 100, RespondDown);
	subkeyup = nh.subscribe<keyboard::Key>("/control/keyboard/keyup", 100, RespondUp);
	subjoy = nh.subscribe<sensor_msgs::Joy>("/control/joystick/joy", 100, RespondJoy);


	//INIT OBJECTS
	keyboardop.Init("/control/teleop/wheels", &nh);

	joyop.Init("/control/teleop/wheels", &nh);

	while(ros::ok()){

		ros::spinOnce();

	if(operatingGlobal){

		if(operatingKeyboard){
			keyboardop.ProcessInput();
		}

		if(operatingJoy){
			joyop.ProcessInput(&ax,&but);
		}

	}

		looprate.sleep();

	}

	return 0;
}
