cmake_minimum_required(VERSION 2.8.3)
project(rover_keyboard_teleop)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
    roscpp
    message_generation
)

include_directories(${catkin_INCLUDE_DIRS} ${roscpp_INCLUDE_DIRS})

add_message_files(
    FILES
    WheelsVel2.msg
    ArmVel5.msg
)

generate_messages(
    DEPENDENCIES
    std_msgs
)

catkin_package(
    CATKIN_DEPENDS message_runtime
)

add_executable(keyboard_teleop
    src/keyboard_teleop/Main.cpp)
target_link_libraries(keyboard_teleop ${catkin_LIBRARIES})

add_executable(keyboard_teleop_old
    src/keyboard_teleop_old/src/Main.cpp
    src/keyboard_teleop_old/src/KeyListener.cpp
    src/keyboard_teleop_old/src/PublisherFloat64.cpp
    src/keyboard_teleop_old/src/PublisherTwist.cpp)
target_link_libraries(keyboard_teleop_old ${catkin_LIBRARIES})
