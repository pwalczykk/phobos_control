#ifndef PUBJOINTSTATE_HPP_
#define PUBJOINTSTATE_HPP_

#include <ros/ros.h>
#include "sensor_msgs/JointState.h"

#include "AddJoint.hpp"

class PubJointState{
    ros::NodeHandle* nh;
    ros::Publisher pub_js;

    std::vector<AddJoint> joints_vec;

public:
    sensor_msgs::JointState msg_js;

public:
    PubJointState(ros::NodeHandle* nh, std::string topic){
        this->nh = nh;
        pub_js = nh->advertise<sensor_msgs::JointState>(topic, 100);

        msg_js.header.seq = 0;
        msg_js.header.stamp = ros::Time::now();
        msg_js.header.frame_id = "phobos_js";
    }

    void Add(std::string joint_name){
        joints_vec.push_back(AddJoint(&this->msg_js, joint_name));
    }

    // void Add(JointConfig *JC, std::string joint_name){
    //     joints_vec.push_back(AddJoint(&this->msg_js, JC, joint_name));
    // }

    void Publish(){
        pub_js.publish(msg_js);
    }
};

#endif
