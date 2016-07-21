#ifndef KEYLISTENER_HPP_
#define KEYLISTENER_HPP_

#include <ros/ros.h>
#include <keyboard/Key.h>

class KeyListener{
    int key_number;

    ros::Subscriber sub_key_down;
    ros::Subscriber sub_key_up;

public:
    KeyListener(){};
    ~KeyListener(){};

    void Init(ros::NodeHandle* nh){
        sub_key_down = nh->subscribe("/keyboard/keydown", 100, &KeyListener::CallbackDown, this);
        sub_key_up = nh->subscribe("/keyboard/keyup", 100, &KeyListener::CallbackUp, this);
    }

    void CallbackDown(const keyboard::Key k){
        this->key_number = k.code;
        KeyDownCallback();
    }

    void CallbackUp(const keyboard::Key k){
        this->key_number = k.code;
        KeyUpCallback();
    }

    int ReturnKey() {
        return key_number;
    }
};

#endif
