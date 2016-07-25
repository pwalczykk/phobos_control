cmake_minimum_required(VERSION 2.8.3)
project(rover_teleop)

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
    src/keyboard_teleop/src/Main.cpp
    src/keyboard_teleop/src/KeyListener.cpp
    src/keyboard_teleop/src/PublisherFloat64.cpp
    src/keyboard_teleop/src/PublisherTwist.cpp)
target_link_libraries(keyboard_teleop ${catkin_LIBRARIES})

add_executable(uart_433_control_transmiter
    src/uart_433_control_transmiter/Main.cpp)
target_link_libraries(uart_433_control_transmiter ${catkin_LIBRARIES})

add_executable(uart_433_control_reciver
    src/uart_433_control_reciver/Main.cpp)
target_link_libraries(uart_433_control_reciver ${catkin_LIBRARIES})
