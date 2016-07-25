#ifndef SUBKEY_HPP_
#define SUBKEY_HPP_

#include <ros/ros.h>
#include <keyboard/Key.h>

#include "Status.hpp"


class SubKey{
    ros::NodeHandle *nh;
    ros::Subscriber sub_key_up;
    ros::Subscriber sub_key_down;

    Status *__status;

public:
    SubKey(ros::NodeHandle *nh, Status *__status){
        this->nh = nh;
        this->__status = __status;
        sub_key_down = nh->subscribe("/keyboard/keydown", 100, &SubKey::CallbackDown, this);
        sub_key_up = nh->subscribe("/keyboard/keyup", 100, &SubKey::CallbackUp, this);
    }

    ~SubKey(){}

    void CallbackDown(const keyboard::Key k){
        __status->KeyDownCallback((int32_t)k.code);
    }

    void CallbackUp(const keyboard::Key k){
        __status->KeyUpCallback((int32_t)k.code);
    }

};

#endif
