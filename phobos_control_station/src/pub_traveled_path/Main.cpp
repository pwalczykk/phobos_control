#include <ros/ros.h>
#include "TraveledPathPublisher.hpp"

int main(int argc, char** argv){
    ros::init(argc, argv, "traveled_path_publisher");
    ros::NodeHandle nh;

    TraveledPathPublisher traveled_path_publisher("/control/localization/pose_ekf", "/control/localization/travelled_path");

    ros::spin();

    return 0;
}
