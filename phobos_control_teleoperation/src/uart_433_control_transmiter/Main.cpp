#include <ros/ros.h>

#include "../../../../../phobos_shared/src/phobos_shared/include/uart_433.hpp"

#include "Status.hpp"
#include "SubKey.hpp"
// #include "SubJoy.hpp"
#include "UART_Tx.hpp"
#include "KeyDefinitions.hpp"

int main(int argc, char** argv){

    ros::init(argc, argv, "uart_433_control_transmiter");
    ros::NodeHandle nh;

    Status __status;

    SubKey sub_key(&nh, &__status);
    // SubJoy sub_joy(&nh, &__status);

    UART_Tx tx("/dev/ttyACM0");

    FrameTeleoperation WORD;

    ros::Rate loop_rate(10);
    while(ros::ok()){ros::spinOnce();
        WORD.wheels_left = __status.wheels_left;
        WORD.wheels_right = __status.wheels_right;
        WORD.link_0 = __status.link_0;
        WORD.link_1 = __status.link_1;
        WORD.link_2 = __status.link_2;
        WORD.link_3 = __status.link_3;
        WORD.link_4 = __status.link_4;
        WORD.grip_force = __status.grip_force;
        WORD.control_mode = 0;
        WORD.control_sum = tx.ControlSum(&WORD);
        tx.Transmit(&WORD);
        // ROS_INFO("TX: %d %d %d %d %d %d %d %d", *(WORD+0), *(WORD+1), *(WORD+2), *(WORD+3), *(WORD+4), *(WORD+5), *(WORD+6), *(WORD+7));
        loop_rate.sleep();
    }

    tx.Close();
    return 0;
}
