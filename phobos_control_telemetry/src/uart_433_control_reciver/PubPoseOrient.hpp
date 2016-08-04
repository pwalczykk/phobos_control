#ifndef PUBPOSEORIENT_HPP_
#define PUBPOSEORIENT_HPP_

#include <ros/ros.h>
#include <geometry_msgs/Pose.h>

class PubPoseOrient{
    ros::NodeHandle *nh;
    ros::Publisher pub;
public:
    geometry_msgs::Pose msg_pose;

public:
    PubPoseOrient(ros::NodeHandle *nh, std::string topic){
        this->nh = nh;
        this->pub = nh->advertise<geometry_msgs::Pose>(topic, 100);
    }

    void Publish(){
        pub.publish(this->msg_pose);
    }

};

#endif
