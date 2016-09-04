#ifndef SUBENCODERS_HPP_
#define SUBENCODERS_HPP_

#include <std_msgs/Int16.h>
#include <phobos_shared/TeleopWheels.h>
#include <phobos_shared/TeleopArm.h>

template <typename ros_Message>
class SubTeleop{
    ros::NodeHandle *nh;
    ros::Subscriber sub;
public:
    bool* new_msg;
    ros_Message msg;
public:
    SubTeleop(std::string topic, ros::NodeHandle *nh, bool* new_msg){
        this->nh = nh;
        this->sub = nh->subscribe(topic, 100, &SubTeleop::MsgInterrupt, this);
    }
    ~SubTeleop(){}

    void MsgInterrupt(const ros_Message msg){
        this->msg = msg;
        *this->new_msg = 1;
    }

    bool NewMsg(){
        if (*new_msg == 1){
            *new_msg = 0;
            return true;
        } else{
            return false;
        }
    }
};
#endif
