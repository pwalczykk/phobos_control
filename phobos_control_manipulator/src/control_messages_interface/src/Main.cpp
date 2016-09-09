#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <phobos_control_manipulator/ControlMsgsConfig.h>

#include "../include/phobos_control_codes.h"

#include "../include/PublisherInt8.hpp"

PublisherInt8 command;
int8_t current_message = DEFAULT_MESSAGE;

void Command(phobos_control_manipulator::ControlMsgsConfig &config, uint32_t level) {
	
  if(config.uzyj_pozycji) current_message = UZYJ_POZYCJI;
  else if(config.stop) current_message = STOP;
  
  else if(config.ustaw_zero_link0) current_message = USTAW_ZERO_LINK0;
  else if(config.ustaw_zero_link1) current_message = USTAW_ZERO_LINK1;
  else if(config.ustaw_zero_link2) current_message = USTAW_ZERO_LINK2;
  else if(config.ustaw_zero_link3) current_message = USTAW_ZERO_LINK3;
  else if(config.ustaw_zero_link4) current_message = USTAW_ZERO_LINK4;
  else if(config.ustaw_zero_grip) current_message = USTAW_ZERO_GRIP;
  
  else if(config.jedz_w_lewo_link0) current_message = JEDZ_W_LEWO_LINK0;
  else if(config.jedz_w_prawo_link0) current_message = JEDZ_W_PRAWO_LINK0;
  
  else if(config.jedz_w_lewo_link1) current_message = JEDZ_W_LEWO_LINK1;
  else if(config.jedz_w_prawo_link1) current_message = JEDZ_W_PRAWO_LINK1;
  
  else if(config.jedz_w_lewo_link2) current_message = JEDZ_W_LEWO_LINK2;
  else if(config.jedz_w_prawo_link2) current_message = JEDZ_W_PRAWO_LINK2;
  
  else if(config.jedz_w_lewo_link3) current_message = JEDZ_W_LEWO_LINK3;
  else if(config.jedz_w_prawo_link3) current_message = JEDZ_W_PRAWO_LINK3;
  
  else if(config.jedz_w_lewo_link4) current_message = JEDZ_W_LEWO_LINK4;
  else if(config.jedz_w_prawo_link4) current_message = JEDZ_W_PRAWO_LINK4;
  
  else if(config.jedz_w_lewo_grip) current_message = JEDZ_W_LEWO_GRIP;
  else if(config.jedz_w_prawo_grip) current_message = JEDZ_W_PRAWO_GRIP;
  
  else if(config.otworz_pojemnik_L) current_message = OTWORZ_POJEMNIK_L;
  else if(config.zamknij_pojemnik_L) current_message = ZAMKNIJ_POJEMNIK_L;
  
  else if(config.otworz_pojemnik_S) current_message = OTWORZ_POJEMNIK_S;
  else if(config.zamknij_pojemnik_S) current_message = ZAMKNIJ_POJEMNIK_S;
  
  else if(config.otworz_pojemnik_P) current_message = OTWORZ_POJEMNIK_P;
  else if(config.zamknij_pojemnik_P) current_message = ZAMKNIJ_POJEMNIK_P;
  
  else current_message = DEFAULT_MESSAGE;
  
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "control_messages_interface");
	ros::NodeHandle nh;
	
	ros::Rate looprate(10);
	
	//DYNAMIC RECONFIGURE
	dynamic_reconfigure::Server<phobos_control_manipulator::ControlMsgsConfig> server;
	dynamic_reconfigure::Server<phobos_control_manipulator::ControlMsgsConfig>::CallbackType f;

	f = boost::bind(&Command, _1, _2);
	server.setCallback(f);
	
	command.Init("/control/teleop/ctrl", &nh);
	
	while(ros::ok()){
		
		ros::spinOnce();
		
		command.Publish(current_message);
		
		looprate.sleep();
		
	}
	
	return 0;
}
