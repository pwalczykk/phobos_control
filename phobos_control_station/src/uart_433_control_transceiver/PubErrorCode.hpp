#ifndef PUBERRORCODE_HPP_
#define PUBERRORCODE_HPP_

#include <ros/ros.h>
#include <std_msgs/Int16.h>

class PubErrorCode{
    ros::NodeHandle *nh;
    ros::Publisher pub;

public:
    std_msgs::Int16 msg;

public:
    PubErrorCode(ros::NodeHandle *nh, std::string topic){
        this->nh = nh;
        this->pub = nh->advertise<std_msgs::Int16>(topic, 100);
    }

    void Publish(){
        pub.publish(this->msg);
    }

    void Publish(int error_code){
        this->msg.data = error_code;
        pub.publish(this->msg);
    }
};

#endif
