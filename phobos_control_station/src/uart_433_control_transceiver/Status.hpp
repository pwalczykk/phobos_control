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
        wheels_left = V_ZERO; wheels_right = V_ZERO;
        link_0 = V_ZERO; link_1 = V_ZERO; link_2 = V_ZERO; link_3 = V_ZERO; link_4 = V_ZERO;
        grip_force = V_ZERO;
    }

    void VelLink0(int16_t link_0){    this->link_0 = link_0;}
    void VelLink1(int16_t link_1){    this->link_1 = link_1;}
    void VelLink2(int16_t link_2){    this->link_2 = link_2;}
    void VelLink3(int16_t link_3){    this->link_3 = link_3;}
    void VelLink4(int16_t link_4){    this->link_4 = link_4;}

    void VelGripper(int16_t grip_force){   this->grip_force = grip_force;}

    void VelWheels(int16_t wheels_left, int16_t wheels_right){
        this->wheels_left = wheels_left;
        this->wheels_right = wheels_right;
    }

    void KeyDownCallback(int16_t key)
    {
        switch(key)
        {
            case Q: VelLink0(V_POS); break;
            case A: VelLink0(V_NEG); break;

            case W: VelLink1(V_POS); break;
            case S: VelLink1(V_NEG); break;

            case E: VelLink2(V_POS); break;
            case D: VelLink2(V_NEG); break;

            case R: VelLink3(V_POS); break;
            case F: VelLink3(V_NEG); break;

            // case T: VelLink4(V_LINK4); break;
            case 116: VelLink4(V_POS); break;
            case G: VelLink4(V_NEG); break;

            case Y: VelGripper(V_POS); break;
            case H: VelGripper(V_NEG); break;

            case U: VelGripper(V_POS); break;
            case J: VelGripper(V_ZERO); break;

            // case N1: VelWheels(V_NEG,V_NEG); break;
            case N2: VelWheels(V_NEG,V_NEG); break;
            // case N3: VelWheels(V_NEG,V_POS); break;
            case N4: VelWheels(V_NEG,V_POS); break;
            case N5: VelWheels(V_ZERO,V_ZERO); break;
            case N6: VelWheels(V_POS,V_NEG); break;
            // case N7: VelWheels(V_POS,V_NEG); break;
            case N8: VelWheels(V_POS,V_POS); break;
            // case N9: VelWheels(V_POS,V_POS); break;
        }
    }

    void KeyUpCallback(int16_t key)
    {
        switch(key)
        {
            case Q: case A: VelLink0(V_ZERO); break;
            case W: case S: VelLink1(V_ZERO); break;
            case E: case D: VelLink2(V_ZERO); break;
            case R: case F: VelLink3(V_ZERO); break;
            // case T: case G: VelLink4(V_ZERO); break;
            case 116: case G: VelLink4(V_ZERO); break;
            case Y: case H: VelGripper(V_ZERO); break;

            case N1: VelWheels(V_ZERO,V_ZERO); break;
            case N2: VelWheels(V_ZERO,V_ZERO); break;
            case N3: VelWheels(V_ZERO,V_ZERO); break;
            case N4: VelWheels(V_ZERO,V_ZERO); break;
            case N5: VelWheels(V_ZERO,V_ZERO); break;
            case N6: VelWheels(V_ZERO,V_ZERO); break;
            case N7: VelWheels(V_ZERO,V_ZERO); break;
            case N8: VelWheels(V_ZERO,V_ZERO); break;
            case N9: VelWheels(V_ZERO,V_ZERO); break;
        }
    }

};

#endif
