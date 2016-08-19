#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

#include "SubPoseStamped.hpp"

int main(int argc, char** argv){
    ros::init(argc, argv, "robot_pose_publisher");
    ros::NodeHandle nh("~");

    std::string parent_link, child_link;
    nh.param("parent_link", parent_link, (std::string)"odom");
    nh.param("child_link", child_link, (std::string)"base_link");

    SubPoseStamped pose("/control/localization/pose_ekf", &nh);

    tf::TransformBroadcaster br;
    tf::Transform transform;

    ros::Rate loop_rate(10);

    while(ros::ok()){
        ros::spinOnce();
        if(pose.new_msg){
            float pose_x = pose.msg.pose.position.x;
            float pose_y = pose.msg.pose.position.y;
            float pose_z = pose.msg.pose.position.z;
            float orient_x = pose.msg.pose.orientation.x;
            float orient_y = pose.msg.pose.orientation.y;
            float orient_z = pose.msg.pose.orientation.z;
            float orient_w = pose.msg.pose.orientation.w;

            transform.setOrigin(tf::Vector3(pose_x, pose_y, pose_z));
            transform.setRotation(tf::Quaternion(orient_x, orient_y, orient_z, orient_w));

            br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), parent_link, child_link));
            pose.new_msg = 0;
        }

        loop_rate.sleep();
    }

    return 0;
}
