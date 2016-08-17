#ifndef STATUS_HPP_
#define STATUS_HPP_

#include "KeyDefinitions.hpp"

struct Status{
    int16_t wheels_left;
    int16_t wheels_right;

    int16_t link_0;
    int16_t link_1;
    int16_t link_2;
    int16_t link_3;
    int16_t link_4;

    int16_t grip_force;

    Status(){
        wheels_left = 0; wheels_right = 0;
        link_0 = 0; link_1 = 0; link_2 = 0; link_3 = 0; link_4 = 0;
        grip_force = 0;
    }

    void VelLink0(int16_t link_0){    this->link_0 = link_0;}
    void VelLink1(int16_t link_1){    this->link_1 = link_1;}
    void VelLink2(int16_t link_2){    this->link_2 = link_2;}
    void VelLink3(int16_t link_3){    this->link_3 = link_3;}
    void VelLink4(int16_t link_4){    this->link_4 = link_4;}

    void VelGripper(int16_t grip_force){   this->grip_force = grip_force;}

    void VelWheels(int16_t linear_vel, int16_t angular_vel){
        this->wheels_left = linear_vel + angular_vel;
        this->wheels_right = linear_vel - angular_vel;
    }

    void KeyDownCallback(int16_t key)
    {
        switch(key)
        {
            case Q: VelLink0(V_LINK0); break;
            case A: VelLink0(-V_LINK0); break;

            case W: VelLink1(V_LINK1); break;
            case S: VelLink1(-V_LINK1); break;

            case E: VelLink2(V_LINK2); break;
            case D: VelLink2(-V_LINK2); break;

            case R: VelLink3(V_LINK3); break;
            case F: VelLink3(-V_LINK3); break;

            // case T: VelLink4(V_LINK4); break;
            case 116: VelLink4(V_LINK4); break;
            case G: VelLink4(-V_LINK4); break;

            case Y: VelGripper(V_GRIP); break;
            case H: VelGripper(-V_GRIP); break;

            case U: VelGripper(V_GRIP); break;
            case J: VelGripper(0); break;

            case N1: VelWheels(-V_LINEAR2,-V_ANGULAR2); break;
            case N2: VelWheels(-V_LINEAR1,0); break;
            case N3: VelWheels(-V_LINEAR2,V_ANGULAR2); break;
            case N4: VelWheels(0,-V_ANGULAR1); break;
            case N5: VelWheels(0,0); break;
            case N6: VelWheels(0,V_ANGULAR1); break;
            case N7: VelWheels(V_LINEAR2,-V_ANGULAR2); break;
            case N8: VelWheels(V_LINEAR1,0); break;
            case N9: VelWheels(V_LINEAR2,V_ANGULAR2); break;
        }
    }

    void KeyUpCallback(int16_t key)
    {
        switch(key)
        {
            case Q: case A: VelLink0(0); break;
            case W: case S: VelLink1(0); break;
            case E: case D: VelLink2(0); break;
            case R: case F: VelLink3(0); break;
            // case T: case G: VelLink4(0); break;
            case 116: case G: VelLink4(0); break;
            case Y: case H: VelGripper(0); break;

            case N1: VelWheels(0,0); break;
            case N2: VelWheels(0,0); break;
            case N3: VelWheels(0,0); break;
            case N4: VelWheels(0,0); break;
            case N5: VelWheels(0,0); break;
            case N6: VelWheels(0,0); break;
            case N7: VelWheels(0,0); break;
            case N8: VelWheels(0,0); break;
            case N9: VelWheels(0,0); break;
        }
    }

};

#endif
