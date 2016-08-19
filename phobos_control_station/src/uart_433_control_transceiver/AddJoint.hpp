#ifndef ADDJOINT_HPP_
#define ADDJOINT_HPP_

#include <ros/ros.h>
#include "sensor_msgs/JointState.h"

class AddJoint{
private:
    ros::NodeHandle nh;
protected:
    sensor_msgs::JointState * msg_js;
    int number;

public:
    AddJoint(sensor_msgs::JointState * msg_js, std::string joint_name){
        this->msg_js = msg_js;
        this->number = this->msg_js->name.size();

        this->msg_js->name.push_back(joint_name);
        this->msg_js->position.push_back(0);
        this->msg_js->velocity.push_back(0);
        this->msg_js->effort.push_back(0);

    }

    void Update(double joint_position){
        this->msg_js->position[number] = joint_position;
    }

};

#endif
