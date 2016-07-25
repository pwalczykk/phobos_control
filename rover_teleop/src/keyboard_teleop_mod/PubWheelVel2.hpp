#ifndef PUBWHEELVEL2_HPP_
#define PUBWHEELVEL2_HPP_

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <rover_teleop/WheelVel2.h>

class PubWheelVel2
{
    rover_teleop::WheelVel2 cmd_vel;

    ros::NodeHandle* nh;
    ros::Publisher pub;

public:
    PubWheelVel2(){};
    ~PubWheelVel2(){};

    void Init(const char* topic, ros::NodeHandle* nh){
        pub = nh->advertise<rover_teleop::WheelVel2>(topic, 100);
        Publish(0);
    }

    void Publish(int32_t wheels_left, int32_t wheels_right){
        msg.wheels_left = wheels_left;
        msg.wheels_right = wheels_right;
        pub.publish(msg);
    }
};

#endif
