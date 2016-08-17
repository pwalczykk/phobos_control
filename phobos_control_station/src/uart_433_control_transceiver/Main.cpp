#include <ros/ros.h>

#include "../../../../../phobos_shared/src/phobos_shared/include/UART_Rx.hpp"
#include "../../../../../phobos_shared/src/phobos_shared/include/UART_Tx.hpp"

#include "KeyDefinitions.hpp"
#include "Status.hpp"

#include "SubKey.hpp"
// #include "SubJoy.hpp"

#include "PubPoseOrient.hpp"
#include "PubJointsState.hpp"

int main(int argc, char **argv){
    int BASIC_RATE;
    int SYNCHRO_RATE;

    ros::init(argc, argv, "uart_433_control_transceiver");
    ros::NodeHandle nh;

    nh.param("basic_rate", BASIC_RATE, 5);
    nh.param("synchro_rate", SYNCHRO_RATE, 5);

    Status __status;

    UART_Tx <FrameTeleoperation>tx("/dev/ttyACM0", TELEOPERATION_DATA_NUM, TELEOPERATION_BUFFOR_SIZE);
    UART_Rx <FrameTelemetry>rx("/dev/ttyACM0",TELEMETRY_DATA_NUM, TELEMETRY_BUFFOR_SIZE);

    SubKey sub_key(&nh, &__status);
    // SubJoy sub_joy(&nh, &__status);

    PubPoseOrient pose_orient(&nh, "/control/localization/pose_ekf");
    PubJointsState joints_state(&nh, "/control/encoders/joints_state");

    int UART_SYNCHRO = 0;
    int ERROR_COUNTER = 0;
    int MAX_ERROR_NUM = 21;

    ros::Rate loop_rate(BASIC_RATE);
    ros::Rate synchro_rate(SYNCHRO_RATE);

    while(ros::ok()){
        // RECIVER
        if(rx.ReadBufferAsChar64()){
            if(rx.CheckControlSum()){

                pose_orient.msg_pose.header.seq++;
                pose_orient.msg_pose.header.stamp = ros::Time::now();

                pose_orient.msg_pose.pose.position.x = rx.WORD.position_x;
                pose_orient.msg_pose.pose.position.y = rx.WORD.position_y;
                pose_orient.msg_pose.pose.position.z = rx.WORD.position_z;

                pose_orient.msg_pose.pose.orientation.x = rx.WORD.orientation_x;
                pose_orient.msg_pose.pose.orientation.y = rx.WORD.orientation_y;
                pose_orient.msg_pose.pose.orientation.z = rx.WORD.orientation_z;
                pose_orient.msg_pose.pose.orientation.w = rx.WORD.orientation_w;

                pose_orient.Publish();

                joints_state.msg_joints.wheel_vel_fl = rx.WORD.wheel_vel_fl;
                joints_state.msg_joints.wheel_vel_fr = rx.WORD.wheel_vel_fr;
                joints_state.msg_joints.wheel_vel_ml = rx.WORD.wheel_vel_ml;
                joints_state.msg_joints.wheel_vel_mr = rx.WORD.wheel_vel_mr;
                joints_state.msg_joints.wheel_vel_bl = rx.WORD.wheel_vel_bl;
                joints_state.msg_joints.wheel_vel_br = rx.WORD.wheel_vel_br;

                joints_state.msg_joints.link_pose_0 = rx.WORD.link_pose_0;
                joints_state.msg_joints.link_pose_1 = rx.WORD.link_pose_1;
                joints_state.msg_joints.link_pose_2 = rx.WORD.link_pose_2;
                joints_state.msg_joints.link_pose_3 = rx.WORD.link_pose_3;
                joints_state.msg_joints.link_pose_4 = rx.WORD.link_pose_4;
                joints_state.msg_joints.grip_pose = rx.WORD.grip_pose;

                joints_state.msg_joints.rocker_pose_l = rx.WORD.rocker_pose_l;
                joints_state.msg_joints.rocker_pose_r = rx.WORD.rocker_pose_r;
                joints_state.msg_joints.bogie_pose_l = rx.WORD.bogie_pose_l;
                joints_state.msg_joints.bogie_pose_r = rx.WORD.bogie_pose_r;

                joints_state.Publish();

                int error_code = rx.WORD.error_code;

                UART_SYNCHRO = 1;
                ERROR_COUNTER = 0;
            }else{
                ERROR_COUNTER++;
            }
        }else{
            ERROR_COUNTER++;
        }

        if(ERROR_COUNTER > MAX_ERROR_NUM){
            // exit(-1);
        }

        // TRANSMITER
        ros::spinOnce();
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
        tx.TransmitAsChar64();

        if(UART_SYNCHRO == 1){
            loop_rate.sleep();
        }else{
            synchro_rate.sleep();
        }
    }
    return 0;
}
