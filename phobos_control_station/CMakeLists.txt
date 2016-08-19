cmake_minimum_required(VERSION 2.8.3)
project(phobos_control_station)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
    roscpp
    image_transport
    cv_bridge
    tf
)

find_package(OpenCV 3.0.0 REQUIRED)
catkin_package()

include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

add_executable(web_video_client
    src/web_video_client/Main.cpp)
target_link_libraries(web_video_client ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} ${catkin_LIBRARIES})

add_executable(uart_433_control_transceiver
    src/uart_433_control_transceiver/Main.cpp)
target_link_libraries(uart_433_control_transceiver ${catkin_LIBRARIES})

add_executable(pub_traveled_path
    src/pub_traveled_path/Main.cpp)
target_link_libraries(pub_traveled_path ${catkin_LIBRARIES})

add_executable(robot_pose_publisher
    src/robot_pose_publisher/Main.cpp)
target_link_libraries(robot_pose_publisher ${catkin_LIBRARIES})
