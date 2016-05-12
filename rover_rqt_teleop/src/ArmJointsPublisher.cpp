#include "../include/ArmJointsPublisher.hpp"

ArmJointsPublisher::ArmJointsPublisher()
{
    pub_joint[0] = nh.advertise<std_msgs::Float64>("/rover/link0_pose", 100);
    pub_joint[1] = nh.advertise<std_msgs::Float64>("/rover/link1_pose", 100);
    pub_joint[2] = nh.advertise<std_msgs::Float64>("/rover/link2_pose", 100);
    pub_joint[3] = nh.advertise<std_msgs::Float64>("/rover/link3_pose", 100);
    pub_joint[4] = nh.advertise<std_msgs::Float64>("/rover/link4_pose", 100);

    pub_joint[5] = nh.advertise<std_msgs::Float64>("/rover/gripper_pose", 100);

    pub_joint[6] = nh.advertise<std_msgs::Float64>("/rover/tower_yaw", 100);
    pub_joint[7] = nh.advertise<std_msgs::Float64>("/rover/tower_pitch", 100);
}

ArmJointsPublisher::~ArmJointsPublisher()
{}

void ArmJointsPublisher::PubJointPose(int i, double pose)
{
    temp_msg.data = pose;
    pub_joint[i].publish(temp_msg);
}
