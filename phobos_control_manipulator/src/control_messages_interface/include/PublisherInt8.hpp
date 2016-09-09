#ifndef PUBLISHERINT8_HPP_
#define PUBLISHERINT8_HPP_

#include <ros/ros.h>
#include <std_msgs/Int8.h>

class PublisherInt8
{
    double current_value;

    std_msgs::Int8 msg;

    ros::NodeHandle* nh;
    ros::Publisher pub;

public:
    PublisherInt8(){};
    PublisherInt8(const char* topic, ros::NodeHandle* nh);
    ~PublisherInt8(){};

    void Init(const char* topic, ros::NodeHandle* nh);

    void Publish(double msg_data);
};

#endif
