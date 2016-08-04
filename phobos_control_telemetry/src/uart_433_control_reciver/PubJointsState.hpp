#ifndef PUBJOINTSSTATE_HPP_
#define PUBJOINTSSTATE_HPP_

#include <ros/ros.h>
#include <phobos_shared/JointsState16.h>

class PubJointsState{
    ros::NodeHandle *nh;
    ros::Publisher pub;
public:
    phobos_shared::JointsState16 msg_joints;

public:
    PubJointsState(ros::NodeHandle *nh, std::string topic){
        this->nh = nh;
        this->pub = nh->advertise<phobos_shared::JointsState16>(topic, 100);
    }

    void Publish(){
        pub.publish(this->msg_joints);
    }

};

#endif
