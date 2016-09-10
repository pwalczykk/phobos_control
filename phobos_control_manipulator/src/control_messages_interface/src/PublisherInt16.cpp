#include "../include/PublisherInt16.hpp"

PublisherInt16::PublisherInt16(const char* topic, ros::NodeHandle* nh)
{
    Init(topic, nh);
}

void PublisherInt16::Init(const char* topic, ros::NodeHandle* nh)
{
    pub = nh->advertise<std_msgs::Int16>(topic, 100);
}

void PublisherInt16::Publish(double msg_data)
{
    msg.data = msg_data;
    pub.publish(msg);
}

void PublisherInt16::Clear(std::string variable){

    nh->setParam(("/control_messages_interface/" + variable).c_str(), false);

}
