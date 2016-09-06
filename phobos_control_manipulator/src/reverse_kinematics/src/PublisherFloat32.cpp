#include "../include/PublisherFloat32.hpp"

PublisherFloat32::PublisherFloat32(const char* topic, ros::NodeHandle* nh)
{
    Init(topic, nh);
}

void PublisherFloat32::Init(const char* topic, ros::NodeHandle* nh)
{
    pub = nh->advertise<std_msgs::Float32>(topic, 100);
    Publish(0);
}

void PublisherFloat32::Publish(double msg_data)
{
    msg.data = msg_data;
    pub.publish(msg);
}
