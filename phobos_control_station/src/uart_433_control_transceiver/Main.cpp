#include <ros/ros.h>

#include "../../../../../phobos_shared/src/phobos_shared/include/UART_Shared.hpp"
#include "../../../../../phobos_shared/src/phobos_shared/include/Conversions.hpp"
#include "../../../../../phobos_shared/src/phobos_shared/include/JointConfig.hpp"

#include "KeyDefinitions.hpp"
#include "Status.hpp"

// #include "SubKey.hpp"
// #include "SubJoy.hpp"

#include "SubTeleop.hpp"

#include "PubPoseOrient.hpp"
#include "PubEncodersAll.hpp"
#include "PubJointState.hpp"
#include "PubErrorCode.hpp"

int main(int argc, char **argv){
    int BASIC_RATE;
    int SYNCHRO_RATE;

    ros::init(argc, argv, "uart_433_control_transceiver");
    ros::NodeHandle nh;

    nh.param("basic_rate", BASIC_RATE, 5);
    nh.param("synchro_rate", SYNCHRO_RATE, 5);

    Status __status;

    // UART_Tx <FrameTeleoperation>tx("/dev/ttyACM0", TELEOPERATION_DATA_NUM, TELEOPERATION_BUFFOR_SIZE);
    // UART_Rx <FrameTelemetry>rx("/dev/ttyACM0",TELEMETRY_DATA_NUM, TELEMETRY_BUFFOR_SIZE);

    UART_Tx TX("/dev/ttyACM0");
    UART_Tx_Encoder <FrameTeleoperationCtrl>    tx_ctrl    (&TX, TO_CTRL_DATA_NUM,      TO_CTRL_DATA_SIZE,      TO_CTRL_BUFFOR_SIZE);
    UART_Tx_Encoder <FrameTeleoperationWheels>  tx_wheels  (&TX, TO_WHEELS_DATA_NUM,    TO_WHEELS_DATA_SIZE,    TO_WHEELS_BUFFOR_SIZE);
    UART_Tx_Encoder <FrameTeleoperationArm>     tx_arm     (&TX, TO_ARM_DATA_NUM,       TO_ARM_DATA_SIZE,       TO_ARM_BUFFOR_SIZE);

    UART_Rx RX("/dev/ttyACM0");
    UART_Rx_Decoder <FrameTelemetryPose>        rx_pose    (&RX, TM_POSE_DATA_NUM,      TM_POSE_DATA_SIZE,      TM_POSE_BUFFOR_SIZE);
    UART_Rx_Decoder <FrameTelemetryOrient>      rx_orient  (&RX, TM_ORIENT_DATA_NUM,    TM_ORIENT_DATA_SIZE,    TM_ORIENT_BUFFOR_SIZE);
    UART_Rx_Decoder <FrameTelemetryWheels>      rx_wheels  (&RX, TM_WHEELS_DATA_NUM,    TM_WHEELS_DATA_SIZE,    TM_WHEELS_BUFFOR_SIZE);
    UART_Rx_Decoder <FrameTelemetryArm>         rx_arm     (&RX, TM_ARM_DATA_NUM,       TM_ARM_DATA_SIZE,       TM_ARM_BUFFOR_SIZE);
    UART_Rx_Decoder <FrameTelemetrySusp>        rx_susp    (&RX, TM_SUSP_DATA_NUM,      TM_SUSP_DATA_SIZE,      TM_SUSP_BUFFOR_SIZE);

    // SubKey sub_key(&nh, &__status);
    // SubJoy sub_joy(&nh, &__status);

    bool NEW_MSG_CTRL = false;
    bool NEW_MSG_WHEELS = false;
    bool NEW_MSG_ARM = false;

    SubTeleop <std_msgs::Int16> sub_ctrl ("/control/teleop/ctrl", &nh, &NEW_MSG_CTRL);
    SubTeleop <phobos_shared::TeleopWheels> sub_wheels ("/control/teleop/wheels", &nh, &NEW_MSG_WHEELS);
    SubTeleop <phobos_shared::TeleopArm> sub_arm ("/control/teleop/arm", &nh, &NEW_MSG_ARM);

    PubErrorCode pub_ctrl(&nh, "/control/rover/error_code");
    PubPoseOrient pub_pose_orient(&nh, "/control/localization/pose_ekf");
    PubEncodersAll pub_encoders_all(&nh, "/control/encoders/all");
    PubJointState pub_joint_state(&nh, "/control/encoders/joint_state");
        pub_joint_state.Add("link_0_joint");
        pub_joint_state.Add("link_1_joint");
        pub_joint_state.Add("link_2_joint");
        pub_joint_state.Add("link_3_joint");
        pub_joint_state.Add("link_4_joint");
        pub_joint_state.Add("finger_l_joint");
        pub_joint_state.Add("finger_r_joint");
        pub_joint_state.Add("rocker_l_bearing_joint");
        pub_joint_state.Add("rocker_r_bearing_joint");
        pub_joint_state.Add("bogie_l_bearing_joint");
        pub_joint_state.Add("bogie_r_bearing_joint");
        pub_joint_state.Add("wheel_bl_joint");
        pub_joint_state.Add("wheel_ml_joint");
        pub_joint_state.Add("wheel_fl_joint");
        pub_joint_state.Add("wheel_br_joint");
        pub_joint_state.Add("wheel_mr_joint");
        pub_joint_state.Add("wheel_fr_joint");

    int UART_SYNCHRO = 0;
    int ERROR_COUNTER = 0;
    int MAX_ERROR_NUM = 5;

    ros::Rate loop_rate(BASIC_RATE);
    ros::Rate synchro_rate(SYNCHRO_RATE);

    while(ros::ok()){
        //RECIVER
        if(RX.ReadBuffor()){
            switch(RX.DecodeMessageType()){
                case FRAME_TM_POSE: {
                    if(rx_pose.CheckControlSum()){
                        rx_pose.DecodeBuffor();

                        ROS_INFO("Pose recived");

                        pub_ctrl.msg.data = rx_pose.FRAME.header.ctrl;
                        pub_ctrl.Publish();

                        pub_pose_orient.msg.pose.position.x = rx_pose.FRAME.position_x;
                        pub_pose_orient.msg.pose.position.y = rx_pose.FRAME.position_y;
                        pub_pose_orient.msg.pose.position.z = rx_pose.FRAME.position_z;
                        pub_pose_orient.Publish();

                        UART_SYNCHRO = 1; ERROR_COUNTER = 0;
                    }
                    break;
                }
                case FRAME_TM_ORIENT: {
                    if(rx_orient.CheckControlSum()){
                        rx_orient.DecodeBuffor();

                        ROS_INFO("Orient recived");


                        pub_ctrl.msg.data = rx_orient.FRAME.header.ctrl;
                        pub_ctrl.Publish();

                        pub_pose_orient.msg.pose.orientation.x = rx_orient.FRAME.orientation_x;
                        pub_pose_orient.msg.pose.orientation.y = rx_orient.FRAME.orientation_y;
                        pub_pose_orient.msg.pose.orientation.z = rx_orient.FRAME.orientation_z;
                        pub_pose_orient.msg.pose.orientation.w = rx_orient.FRAME.orientation_w;
                        pub_pose_orient.Publish();

                        UART_SYNCHRO = 1; ERROR_COUNTER = 0;
                    }
                    break;
                }
                case FRAME_TM_WHEELS: {
                    if(rx_wheels.CheckControlSum()){
                        rx_wheels.DecodeBuffor();

                        ROS_INFO("Wheels recived");


                        pub_ctrl.msg.data = rx_wheels.FRAME.header.ctrl;
                        pub_ctrl.Publish();

                        pub_encoders_all.msg.wheel_vel_fl = rx_wheels.FRAME.wheel_vel_fl;
                        pub_encoders_all.msg.wheel_vel_fr = rx_wheels.FRAME.wheel_vel_fr;
                        pub_encoders_all.msg.wheel_vel_ml = rx_wheels.FRAME.wheel_vel_ml;
                        pub_encoders_all.msg.wheel_vel_mr = rx_wheels.FRAME.wheel_vel_mr;
                        pub_encoders_all.msg.wheel_vel_bl = rx_wheels.FRAME.wheel_vel_bl;
                        pub_encoders_all.msg.wheel_vel_br = rx_wheels.FRAME.wheel_vel_br;
                        pub_encoders_all.Publish();

                        UART_SYNCHRO = 1; ERROR_COUNTER = 0;
                    }
                    break;
                }
                case FRAME_TM_ARM: {
                    if(rx_arm.CheckControlSum()){
                        rx_arm.DecodeBuffor();

                        ROS_INFO("Arm recived");


                        pub_ctrl.msg.data = rx_arm.FRAME.header.ctrl;
                        pub_ctrl.Publish();

                        pub_encoders_all.msg.link_pose_0 = rx_arm.FRAME.link_pose_0;
                        pub_encoders_all.msg.link_pose_1 = rx_arm.FRAME.link_pose_1;
                        pub_encoders_all.msg.link_pose_2 = rx_arm.FRAME.link_pose_2;
                        pub_encoders_all.msg.link_pose_3 = rx_arm.FRAME.link_pose_3;
                        pub_encoders_all.msg.link_pose_4 = rx_arm.FRAME.link_pose_4;
                        pub_encoders_all.msg.grip_pose = rx_arm.FRAME.grip_pose;
                        pub_encoders_all.Publish();

                        UART_SYNCHRO = 1; ERROR_COUNTER = 0;
                    }
                    break;
                }
                case FRAME_TM_SUSP: {
                    if(rx_susp.CheckControlSum()){
                        rx_susp.DecodeBuffor();

                        ROS_INFO("Susp recived");


                        pub_ctrl.msg.data = rx_susp.FRAME.header.ctrl;
                        pub_ctrl.Publish();

                        pub_encoders_all.msg.rocker_pose_l = rx_susp.FRAME.rocker_pose_l;
                        pub_encoders_all.msg.rocker_pose_r = rx_susp.FRAME.rocker_pose_r;
                        pub_encoders_all.msg.bogie_pose_l = rx_susp.FRAME.bogie_pose_l;
                        pub_encoders_all.msg.bogie_pose_r = rx_susp.FRAME.bogie_pose_r;
                        pub_encoders_all.Publish();

                        UART_SYNCHRO = 1; ERROR_COUNTER = 0;
                    }
                    break;
                }
                default : {
                    ROS_WARN("RX frame not recognized! Type: %c (ASCII: %d)", RX.DecodeMessageType(), (int)RX.DecodeMessageType());
                    ERROR_COUNTER++;
                }
            }
        }else{
            ERROR_COUNTER++;
        }

        if(ERROR_COUNTER > MAX_ERROR_NUM){
            ROS_ERROR("%d errors in a row - exiting!!", ERROR_COUNTER);
            exit(-1);
        }

        // TRANSMITER
        ros::spinOnce();
        if(sub_wheels.NewMsg()){
            tx_wheels.FRAME.header.type = FRAME_TO_WHEELS;
            tx_wheels.FRAME.header.ctrl = sub_ctrl.msg.data;

            tx_wheels.FRAME.wheels_left = sub_wheels.msg.wheels_left;
            tx_wheels.FRAME.wheels_right = sub_wheels.msg.wheels_right;

            tx_wheels.EncodeBuffor();

            TX.Transmit(TO_WHEELS_BUFFOR_SIZE);
        }

        else if(sub_arm.NewMsg()){
            tx_arm.FRAME.header.type = FRAME_TO_ARM;
            tx_arm.FRAME.header.ctrl = sub_ctrl.msg.data;

            tx_arm.FRAME.link_0 = sub_arm.msg.link_0;
            tx_arm.FRAME.link_1 = sub_arm.msg.link_1;
            tx_arm.FRAME.link_2 = sub_arm.msg.link_2;
            tx_arm.FRAME.link_3 = sub_arm.msg.link_3;
            tx_arm.FRAME.link_4 = sub_arm.msg.link_4;
            tx_arm.FRAME.grip = sub_arm.msg.grip;

            tx_arm.EncodeBuffor();

            TX.Transmit(TO_ARM_BUFFOR_SIZE);
        }

        else {

            ROS_INFO("CTRL trasnmitting");
            tx_ctrl.FRAME.header.type = FRAME_TO_CTRL;
            tx_ctrl.FRAME.header.ctrl = sub_ctrl.msg.data;
            // tx_ctrl.FRAME.header.ctrl = 0;

            tx_ctrl.EncodeBuffor();

            TX.Transmit(TO_CTRL_BUFFOR_SIZE);
        }


        if(UART_SYNCHRO == 1){
            loop_rate.sleep();
        }else{
            synchro_rate.sleep();
        }
    }

    return 0;
}
