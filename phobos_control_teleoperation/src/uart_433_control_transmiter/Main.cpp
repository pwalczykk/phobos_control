#include <ros/ros.h>

#include "../../../../../phobos_shared/src/phobos_shared/include/UART_Tx.hpp"

#include "Status.hpp"
#include "SubKey.hpp"
// #include "SubJoy.hpp"
#include "KeyDefinitions.hpp"

int main(int argc, char** argv){

    ros::init(argc, argv, "uart_433_control_transmiter");
    ros::NodeHandle nh;

    Status __status;

    UART_Tx <FrameTeleoperation>tx("/dev/ttyACM0", TELEOPERATION_DATA_NUM);

    SubKey sub_key(&nh, &__status);
    // SubJoy sub_joy(&nh, &__status);

    ros::Rate loop_rate(10);
    while(ros::ok()){ros::spinOnce();
        tx.WORD.wheels_left = __status.wheels_left;
        tx.WORD.wheels_right = __status.wheels_right;
        tx.WORD.link_0 = __status.link_0;
        tx.WORD.link_1 = __status.link_1;
        tx.WORD.link_2 = __status.link_2;
        tx.WORD.link_3 = __status.link_3;
        tx.WORD.link_4 = __status.link_4;
        tx.WORD.grip_force = __status.grip_force;
        tx.WORD.control_mode = 0;
        tx.WORD.control_sum = tx.ControlSum();
        // tx.Transmit();
        tx.TransmitAsString();
        // ROS_INFO("TX: %d %d %d %d %d %d %d %d %d", *(tx.WORD.begin+0), *(tx.WORD.begin+1), *(tx.WORD.begin+2), *(tx.WORD.begin+3), *(tx.WORD.begin+4), *(tx.WORD.begin+5), *(tx.WORD.begin+6), *(tx.WORD.begin+7), *(tx.WORD.begin+8));
        loop_rate.sleep();
    }

    tx.Close();
    return 0;
}
