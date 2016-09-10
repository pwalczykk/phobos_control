#ifndef PUBLISHERINT16_HPP_
#define PUBLISHERINT16_HPP_

#include <ros/ros.h>
#include <std_msgs/Int16.h>

class PublisherInt16
{
    double current_value;

    std_msgs::Int16 msg;

    ros::NodeHandle* nh;
    ros::Publisher pub;

public:
    PublisherInt16(){};
    PublisherInt16(const char* topic, ros::NodeHandle* nh);
    ~PublisherInt16(){};

    void Init(const char* topic, ros::NodeHandle* nh);
    void Clear(std::string variable);

    void Publish(double msg_data);
};

#endif
