cmake_minimum_required(VERSION 2.8.3)
project(rover_keyboard_teleop)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    rospy
)

catkin_package()

add_executable(keyboard_teleop src/Main.cpp src/KeyListener.cpp src/PublisherFloat64.cpp src/PublisherTwist.cpp)
target_link_libraries(keyboard_teleop ${catkin_LIBRARIES})
