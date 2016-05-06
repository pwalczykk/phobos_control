#include <ros/ros.h>
#include "../include/ArmTeleop.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "gazebo_sim_controller");

    ArmTeleop arm_telop;

    arm_telop.PublishAll();

    ros::spin();
}
