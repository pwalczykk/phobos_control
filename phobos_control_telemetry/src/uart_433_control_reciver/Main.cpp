#include <ros/ros.h>

#include "../../../../../phobos_shared/src/phobos_shared/include/uart_433.hpp"

#include "PubPoseOrient.hpp"
#include "PubJointsState.hpp"
#include "UART_Rx.hpp"

int main(int argc, char **argv){

    ros::init(argc, argv, "uart_433_control_reciver");
    ros::NodeHandle nh;

    UART_Rx <FrameTelemetry>rx("/dev/ttyACM0",TELEMETRY_DATA_NUM);

    PubPoseOrient pose_orient(&nh, "/control/localization/pose_ekf");
    PubJointsState joints_state(&nh, "/control/encoders/joints_state");


    ros::Rate loop_rate(10);

    while(ros::ok()){
        if(rx.ReadBuffer()){
            if(rx.CheckControlSum()){
                pose_orient.msg_pose.position.x = rx.WORD.position_x;
                pose_orient.msg_pose.position.y = rx.WORD.position_y;
                pose_orient.msg_pose.position.z = rx.WORD.position_z;

                pose_orient.msg_pose.orientation.x = rx.WORD.orientation_x;
                pose_orient.msg_pose.orientation.y = rx.WORD.orientation_y;
                pose_orient.msg_pose.orientation.z = rx.WORD.orientation_z;
                pose_orient.msg_pose.orientation.w = rx.WORD.orientation_w;

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
            }
            for(int i = 0; i < TELEMETRY_DATA_NUM; i++){ printf("%d ", *(rx.WORD.begin + i));}   printf("\n");
        }
        loop_rate.sleep();
    }
    return 0;
}
