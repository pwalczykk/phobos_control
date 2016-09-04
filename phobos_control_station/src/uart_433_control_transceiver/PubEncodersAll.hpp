#ifndef PUBENCODERSALL_HPP_
#define PUBENCODERSALL_HPP_

#include <ros/ros.h>
#include <phobos_shared/EncodersAll.h>

class PubEncodersAll{
    ros::NodeHandle *nh;
    ros::Publisher pub;
public:
    phobos_shared::EncodersAll msg;

public:
    PubEncodersAll(ros::NodeHandle *nh, std::string topic){
        this->nh = nh;
        this->pub = nh->advertise<phobos_shared::EncodersAll>(topic, 100);
    }

    void Publish(){
        pub.publish(this->msg);
    }

};

#endif
