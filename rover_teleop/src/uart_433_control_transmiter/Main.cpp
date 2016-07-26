#include <ros/ros.h>

#include "Status.hpp"
#include "SubKey.hpp"
// #include "SubJoy.hpp"
#include "UART_Tx.hpp"
#include "KeyDefinitions.hpp"

int main(int argc, char** argv){

    ros::init(argc, argv, "keyboard_teleop");
    ros::NodeHandle nh;

    Status __status;

    SubKey sub_key(&nh, &__status);
    // SubJoy sub_joy(&nh, &__status);

    UART_Tx tx("/dev/ttyACM0");
    int32_t* word = (int32_t*) malloc((BUFF_SIZE) * sizeof(int32_t));

    ros::Rate loop_rate(10);
    while(ros::ok()){ros::spinOnce();
        *(word+0) = __status.wheels_left;
        *(word+1) = __status.wheels_right;
        *(word+2) = __status.link_0;
        *(word+3) = __status.link_1;
        *(word+4) = __status.link_2;
        *(word+5) = __status.link_3;
        *(word+6) = __status.link_4;
        *(word+7) = tx.ControlSum(word);
        tx.Transmit(word);
        ROS_INFO("TX: %d %d %d %d %d %d %d %d", *(word+0), *(word+1), *(word+2), *(word+3), *(word+4), *(word+5), *(word+6), *(word+7));
        loop_rate.sleep();
    }

    free(word);
    return 0;
}
