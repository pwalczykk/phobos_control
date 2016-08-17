#ifndef IMAGEPUBLISHER_HPP_
#define IMAGEPUBLISHER_HPP_

#include "CameraHandler.hpp"

#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CameraInfo.h>
#include <std_msgs/Header.h>

class ImageHandler : public CameraHandler{
    ros::NodeHandle nh;
    image_transport::ImageTransport* it;
    image_transport::Publisher pub_img;

protected:
    sensor_msgs::ImagePtr img;
    std_msgs::Header header;
    std::string window_name;

public:
    ImageHandler(std::string stream_addres, std::string publisher_topic) : CameraHandler(stream_addres){

        it = new image_transport::ImageTransport(nh);
        pub_img = it->advertise(publisher_topic, 1);

        header.seq = 0;
        header.frame_id = "ip";
    }

    void Init(){
        CameraHandler::Init();
    }

    void CreateWindow(std::string name, int pose_x, int pose_y){
        this->window_name = name;
        cv::namedWindow(name, CV_WINDOW_AUTOSIZE);
        cv::moveWindow(name, pose_x, pose_y);
    }

    void CreateWindow(std::string name, int pose_x, int pose_y, int size_x, int size_y){
        this->window_name = name;
        cv::namedWindow(name, CV_WINDOW_NORMAL);
        cv::moveWindow(name, pose_x, pose_y);
        cv::resizeWindow(name, size_x, size_y);
    }

    void ViewImage(){
        cv::imshow(window_name, CameraHandler::frame);
        cv::waitKey(1);
    }

    void PublishImage(){
        header.seq++;
        header.stamp = ros::Time::now();

        CameraHandler::Capture();

        img = cv_bridge::CvImage(header, "bgr8", CameraHandler::frame).toImageMsg();
        pub_img.publish(img);
    }
};

#endif
