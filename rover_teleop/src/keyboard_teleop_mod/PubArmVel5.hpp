#ifndef PUBARMPOSE5_HPP_
#define PUBARMPOSE5_HPP_

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <rover_teleop/ArmVel5.h>


class PubArmPose5
{
    geometry_msgs::Twist cmd_vel;

    ros::NodeHandle* nh;
    ros::Publisher pub;

public:
    PubArmPose5(){};
    ~PubArmPose5(){};

    void Init(const char* topic, ros::NodeHandle* nh){
        pub = nh->advertise<rover_teleop::ArmVel5>(topic, 100);
        Publish(0);
    }

    void Publish(int32_t link_0, int32_t link_1, int32_t link_2, int32_t link_3, int32_t link_4){
        msg.link_0 = link_0;
        msg.link_1 = link_1;
        msg.link_2 = link_2;
        msg.link_3 = link_3;
        msg.link_4 = link_4;
        pub.publish(msg);
    }
};

#endif
