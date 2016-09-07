#ifndef PUBENCODERSALL_HPP_
#define PUBENCODERSALL_HPP_

#include <ros/ros.h>
#include <phobos_shared/EncodersAllFloat.h>

class PubEncodersAll{
    ros::NodeHandle *nh;
    ros::Publisher pub;
public:
    phobos_shared::EncodersAllFloat msg;

public:
    PubEncodersAll(ros::NodeHandle *nh, std::string topic){
        this->nh = nh;
        this->pub = nh->advertise<phobos_shared::EncodersAllFloat>(topic, 100);
    }

    void Publish(){
        pub.publish(this->msg);
    }

};

#endif
