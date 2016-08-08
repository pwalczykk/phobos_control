cmake_minimum_required(VERSION 2.8.3)
project(phobos_control_vision)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    image_transport
    cv_bridge
)

find_package(OpenCV 3.0.0 REQUIRED)
catkin_package()

include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_executable(web_video_client
    src/web_video_client/Main.cpp)
target_link_libraries(web_video_client ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} ${catkin_LIBRARIES})
