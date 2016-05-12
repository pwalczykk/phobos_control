#ifndef DYNAMICRECONFIGURE_HPP_
#define DYNAMICRECONFIGURE_HPP_

#include "../include/ArmJointsPublisher.hpp"

#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <rover_rqt_teleop/ArmTeleopConfig.h>

class ArmTeleop
{
    double joint[JOINTS_NUM];
    bool joint_mod[JOINTS_NUM];

    ArmJointsPublisher arm_joints_publisher;

    dynamic_reconfigure::Server<rover_rqt_teleop::ArmTeleopConfig> server;
    dynamic_reconfigure::Server<rover_rqt_teleop::ArmTeleopConfig>::CallbackType f;
public:
    ArmTeleop();
    ~ArmTeleop();

    void PublishAll();

    void Callback(rover_rqt_teleop::ArmTeleopConfig &config, uint32_t level);
};

#endif
