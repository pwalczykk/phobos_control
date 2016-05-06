#include "../include/ArmTeleop.hpp"

ArmTeleop::ArmTeleop()
{
    f = boost::bind(&ArmTeleop::Callback, this, _1, _2);
    server.setCallback(f);

    this->arm_joints_publisher = ArmJointsPublisher();

    this->joint[0] = 0;
    this->joint[1] = 0;
    this->joint[2] = 0;
    this->joint[3] = 0;
    this->joint[4] = 0;

    this->joint[5] = 0;
    this->joint[6] = 0;

    this->joint[7] = 0;
}

ArmTeleop::~ArmTeleop()
{}

void ArmTeleop::PublishAll()
{
    for(int i = 0; i < JOINTS_NUM; i++)
    {
        arm_joints_publisher.PubJointPose(i, joint[i]);
    }
}

void ArmTeleop::Callback(rover_simulation::ArmTeleopConfig &config, uint32_t level)
{
    double joint_temp[JOINTS_NUM];

    joint_temp[0] = config.joint0;
    joint_temp[1] = config.joint1;
    joint_temp[2] = config.joint2;
    joint_temp[3] = config.joint3;
    joint_temp[4] = config.joint4;

    joint_temp[5] = config.joint5;
    joint_temp[6] = config.joint6;

    joint_temp[7] = config.joint7;

    for(int i = 0; i < JOINTS_NUM; i++)
    {
        this->joint_mod[i] = 0;
        if(this->joint[i] != joint_temp[i])
        {
            this->joint[i] = joint_temp[i];
            this->joint_mod[i] = 1;
        }
    }

    for(int i = 0; i <JOINTS_NUM; i++)
    {
        if(joint_mod[i])
        {
            arm_joints_publisher.PubJointPose(i, joint[i]);
        }
    }
}
