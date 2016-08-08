#ifndef PUBPOSEORIENT_HPP_
#define PUBPOSEORIENT_HPP_

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

class PubPoseOrient{
    ros::NodeHandle *nh;
    ros::Publisher pub;
public:
    geometry_msgs::PoseStamped msg_pose;

public:
    PubPoseOrient(ros::NodeHandle *nh, std::string topic){
        this->nh = nh;
        this->pub = nh->advertise<geometry_msgs::PoseStamped>(topic, 100);

        this->msg_pose.header.seq = 0;
        this->msg_pose.header.frame_id = "odom";
    }

    void Publish(){
        pub.publish(this->msg_pose);
    }

};

#endif
