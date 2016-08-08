cmake_minimum_required(VERSION 2.8.3)
project(phobos_control_telemetry)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
    roscpp
)

catkin_package()

add_executable(uart_433_control_reciver
    src/uart_433_control_reciver/Main.cpp)
target_link_libraries(uart_433_control_reciver ${catkin_LIBRARIES})

add_executable(pub_traveled_path
    src/pub_traveled_path/Main.cpp)
target_link_libraries(pub_traveled_path ${catkin_LIBRARIES})
