#include <ros/ros.h>

#include "../../../../../phobos_shared/src/phobos_shared/include/UART_Rx.hpp"
#include "../../../../../phobos_shared/src/phobos_shared/include/UART_Tx.hpp"
#include "../../../../../phobos_shared/src/phobos_shared/include/Conversions.hpp"
#include "../../../../../phobos_shared/src/phobos_shared/include/JointConfig.hpp"


#include "KeyDefinitions.hpp"
#include "Status.hpp"

#include "SubKey.hpp"
// #include "SubJoy.hpp"

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

    UART_Tx <FrameTeleoperation>tx("/dev/ttyACM0", TELEOPERATION_DATA_NUM, TELEOPERATION_BUFFOR_SIZE);
    UART_Rx <FrameTelemetry>rx("/dev/ttyACM0",TELEMETRY_DATA_NUM, TELEMETRY_BUFFOR_SIZE);

    SubKey sub_key(&nh, &__status);
    // SubJoy sub_joy(&nh, &__status);

    PubErrorCode security_error(&nh, "/control/security/error_code");
    PubPoseOrient pose_orient(&nh, "/control/localization/pose_ekf");
    PubEncodersAll encoders_all(&nh, "/control/encoders/all");
    PubJointState joint_state(&nh, "/control/encoders/joint_state");
        joint_state.Add("link_0_joint");
        joint_state.Add("link_1_joint");
        joint_state.Add("link_2_joint");
        joint_state.Add("link_3_joint");
        joint_state.Add("link_4_joint");
        joint_state.Add("finger_l_joint");
        joint_state.Add("finger_r_joint");
        joint_state.Add("rocker_l_bearing_joint");
        joint_state.Add("rocker_r_bearing_joint");
        joint_state.Add("bogie_l_bearing_joint");
        joint_state.Add("bogie_r_bearing_joint");
        joint_state.Add("wheel_bl_joint");
        joint_state.Add("wheel_ml_joint");
        joint_state.Add("wheel_fl_joint");
        joint_state.Add("wheel_br_joint");
        joint_state.Add("wheel_mr_joint");
        joint_state.Add("wheel_fr_joint");

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

                pose_orient.msg_pose.pose.position.x = Pose_Int2Float(rx.WORD.position_x);
                pose_orient.msg_pose.pose.position.y = Pose_Int2Float(rx.WORD.position_y);
                pose_orient.msg_pose.pose.position.z = Pose_Int2Float(rx.WORD.position_z);

                pose_orient.msg_pose.pose.orientation.x = Orient_Int2Float(rx.WORD.orientation_x);
                pose_orient.msg_pose.pose.orientation.y = Orient_Int2Float(rx.WORD.orientation_y);
                pose_orient.msg_pose.pose.orientation.z = Orient_Int2Float(rx.WORD.orientation_z);
                pose_orient.msg_pose.pose.orientation.w = Orient_Int2Float(rx.WORD.orientation_w);

                pose_orient.Publish();

                encoders_all.msg_encoders.wheel_vel_fl = rx.WORD.wheel_vel_fl;
                encoders_all.msg_encoders.wheel_vel_fr = rx.WORD.wheel_vel_fr;
                encoders_all.msg_encoders.wheel_vel_ml = rx.WORD.wheel_vel_ml;
                encoders_all.msg_encoders.wheel_vel_mr = rx.WORD.wheel_vel_mr;
                encoders_all.msg_encoders.wheel_vel_bl = rx.WORD.wheel_vel_bl;
                encoders_all.msg_encoders.wheel_vel_br = rx.WORD.wheel_vel_br;

                encoders_all.msg_encoders.link_pose_0 = rx.WORD.link_pose_0;
                encoders_all.msg_encoders.link_pose_1 = rx.WORD.link_pose_1;
                encoders_all.msg_encoders.link_pose_2 = rx.WORD.link_pose_2;
                encoders_all.msg_encoders.link_pose_3 = rx.WORD.link_pose_3;
                encoders_all.msg_encoders.link_pose_4 = rx.WORD.link_pose_4;
                encoders_all.msg_encoders.grip_pose = rx.WORD.grip_pose;

                encoders_all.msg_encoders.rocker_pose_l = rx.WORD.rocker_pose_l;
                encoders_all.msg_encoders.rocker_pose_r = rx.WORD.rocker_pose_r;
                encoders_all.msg_encoders.bogie_pose_l = rx.WORD.bogie_pose_l;
                encoders_all.msg_encoders.bogie_pose_r = rx.WORD.bogie_pose_r;

                encoders_all.Publish();

                joint_state.msg_js.header.seq++;
                joint_state.msg_js.header.stamp = ros::Time::now();

                joint_state.msg_js.position[0] = LINK_0.IMP2RAD(rx.WORD.link_pose_0);
                joint_state.msg_js.position[1] = LINK_1.IMP2RAD(rx.WORD.link_pose_1);
                joint_state.msg_js.position[2] = LINK_2.IMP2RAD(rx.WORD.link_pose_2);
                joint_state.msg_js.position[3] = LINK_3.IMP2RAD(rx.WORD.link_pose_3);
                joint_state.msg_js.position[4] = LINK_4.IMP2RAD(rx.WORD.link_pose_4);
                joint_state.msg_js.position[5] = GRIPPER.IMP2RAD(rx.WORD.grip_pose);
                joint_state.msg_js.position[6] = GRIPPER.IMP2RAD(rx.WORD.grip_pose);

                joint_state.msg_js.position[7] = ROCKER.IMP2RAD(rx.WORD.rocker_pose_l);
                joint_state.msg_js.position[8] = ROCKER.IMP2RAD(rx.WORD.rocker_pose_r);
                joint_state.msg_js.position[9] = BOGIE.IMP2RAD(rx.WORD.bogie_pose_l);
                joint_state.msg_js.position[10] = BOGIE.IMP2RAD(rx.WORD.bogie_pose_r);

                joint_state.msg_js.position[11] = WHEEL.IMP2RAD(rx.WORD.wheel_vel_fl);
                joint_state.msg_js.position[12] = WHEEL.IMP2RAD(rx.WORD.wheel_vel_fr);
                joint_state.msg_js.position[13] = WHEEL.IMP2RAD(rx.WORD.wheel_vel_ml);
                joint_state.msg_js.position[14] = WHEEL.IMP2RAD(rx.WORD.wheel_vel_mr);
                joint_state.msg_js.position[15] = WHEEL.IMP2RAD(rx.WORD.wheel_vel_bl);
                joint_state.msg_js.position[16] = WHEEL.IMP2RAD(rx.WORD.wheel_vel_br);

                joint_state.Publish();

                security_error.Publish(rx.WORD.error_code);

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
