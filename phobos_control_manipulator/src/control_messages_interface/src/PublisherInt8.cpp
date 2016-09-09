#include "../include/PublisherInt8.hpp"

PublisherInt8::PublisherInt8(const char* topic, ros::NodeHandle* nh)
{
    Init(topic, nh);
}

void PublisherInt8::Init(const char* topic, ros::NodeHandle* nh)
{
    pub = nh->advertise<std_msgs::Int8>(topic, 100);
}

void PublisherInt8::Publish(double msg_data)
{
    msg.data = msg_data;
    pub.publish(msg);
}
