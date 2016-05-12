#ifndef ARMJOINTSPUBLISHER_HPP_
#define ARMJOINTSPUBLISHER_HPP_

#define JOINTS_NUM 8

#include <ros/ros.h>
#include <std_msgs/Float64.h>

class ArmJointsPublisher{
    std_msgs::Float64 temp_msg;

    ros::NodeHandle nh;

    ros::Publisher pub_joint[JOINTS_NUM];

public:
    ArmJointsPublisher();
    ~ArmJointsPublisher();

    void PubJointPose(int i, double pose);

};

#endif
