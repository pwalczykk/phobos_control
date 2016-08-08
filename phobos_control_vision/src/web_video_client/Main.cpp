#include "CameraHandler.hpp"
#include "ImageHandler.hpp"
#include <ros/ros.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "web_video_client");
    ros::NodeHandle nh("~");

    // Image handler options
    bool publish_image = 1;
    bool view_image = 1;

    std::string stream_addres, publisher_topic, window_name;
    if(!nh.getParam("stream_addres", stream_addres)) {ROS_ERROR("No stream_addres!"); exit(-1);}
    if(!nh.getParam("publisher_topic", publisher_topic)) { publish_image = 0; }
    if(!nh.getParam("window_name", window_name)) { view_image = 0; }

    ImageHandler image_handler(stream_addres, publisher_topic);
    image_handler.Init();

    // Video viewer options
    int pose_x, pose_y, size_x, size_y;
    nh.param("pose_x", pose_x, 1);
    nh.param("pose_y", pose_y, 1);

    if(nh.getParam("size_x", size_x) && nh.getParam("size_y", size_y)){
        image_handler.CreateWindow(window_name, pose_x, pose_y, size_x, size_y);
    }else{
        image_handler.CreateWindow(window_name, pose_x, pose_y);
    }

    // Main loop
    ros::Rate loop_rate(10);

    if(publish_image && !view_image){
        while(ros::ok()){
            image_handler.PublishImage();
            loop_rate.sleep();
        }
    }else if(!publish_image && view_image){
        while(ros::ok()){
            image_handler.ViewImage();
            loop_rate.sleep();
        }
    }else if(publish_image && view_image){
        while(ros::ok()){
            image_handler.ViewImage();
            image_handler.PublishImage();
            loop_rate.sleep();
        }
    }else{
        ROS_WARN("Nothing to do - closing web_video_client");
    }

    image_handler.CameraHandler::Release();

    return 0;
}
