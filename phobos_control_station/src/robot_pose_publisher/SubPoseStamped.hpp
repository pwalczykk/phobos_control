#ifndef SUBPOSESTAMPED_HPP_
#define SUBPOSESTAMPED_HPP_

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

class SubPoseStamped{
    ros::NodeHandle *nh;
    ros::Subscriber sub;

public:
    geometry_msgs::PoseStamped msg;
    bool new_msg;

public:
    SubPoseStamped(std::string topic,ros::NodeHandle *nh){
        this->nh = nh;
        this->sub = nh->subscribe(topic, 100, &SubPoseStamped::MsgInterrupt, this);

        this->new_msg = 0;

        this->msg.pose.position.x = 0;
        this->msg.pose.position.y = 0;
        this->msg.pose.position.z = 0;
        this->msg.pose.orientation.x = 0;
        this->msg.pose.orientation.y = 0;
        this->msg.pose.orientation.z = 0;
        this->msg.pose.orientation.w = 0;
    }
    ~SubPoseStamped(){}

    void MsgInterrupt(const geometry_msgs::PoseStamped msg){
        this->msg = msg;
        this->new_msg = 1;
    }
};

#endif
