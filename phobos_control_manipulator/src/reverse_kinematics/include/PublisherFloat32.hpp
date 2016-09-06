#ifndef PUBLISHERFLOAT32_HPP_
#define PUBLISHERFLOAT32_HPP_

#include <ros/ros.h>
#include <std_msgs/Float32.h>

class PublisherFloat32
{
    double current_value;

    std_msgs::Float32 msg;

    ros::NodeHandle* nh;
    ros::Publisher pub;

public:
    PublisherFloat32(){};
    PublisherFloat32(const char* topic, ros::NodeHandle* nh);
    ~PublisherFloat32(){};

    void Init(const char* topic, ros::NodeHandle* nh);

    void Publish(double msg_data);
};

#endif
