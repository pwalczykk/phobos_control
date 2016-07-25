#include <ros/ros.h>

#include "PubPoseOrient.hpp"
#include "UART_Rx.hpp"

int main(int argc, char **argv){

    ros::init(argc, argv, "uart_433_control_reciver");
    ros::NodeHandle nh;

    PubPoseOrient pub_pose_orient(&nh, "/rover/odometry/filtered");

    UART_Rx rx("/dev/ttyACM0");

    ros::Rate loop_rate(20);

    while(ros::ok()){
        if(rx.ReadBuffer()){
            if(rx.CheckControlSum()){
                pub_pose_orient.msg_pose.position.x = rx.rx_buffer[0];
                pub_pose_orient.msg_pose.position.y = rx.rx_buffer[1];
                pub_pose_orient.msg_pose.position.z = rx.rx_buffer[2];

                pub_pose_orient.msg_pose.orientation.x = rx.rx_buffer[3];
                pub_pose_orient.msg_pose.orientation.y = rx.rx_buffer[4];
                pub_pose_orient.msg_pose.orientation.z = rx.rx_buffer[5];
                pub_pose_orient.msg_pose.orientation.w = rx.rx_buffer[6];

                pub_pose_orient.Publish();
            }
            ROS_INFO("RX: %d %d %d %d %d %d %d %d", *(rx.rx_buffer+0), *(rx.rx_buffer+1), *(rx.rx_buffer+2), *(rx.rx_buffer+3), *(rx.rx_buffer+4), *(rx.rx_buffer+5), *(rx.rx_buffer+6), *(rx.rx_buffer+7));
        }
        loop_rate.sleep();
    }
    return 0;
}
