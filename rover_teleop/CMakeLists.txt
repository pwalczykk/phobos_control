cmake_minimum_required(VERSION 2.8.3)
project(rover_teleop)

find_package(catkin REQUIRED COMPONENTS
    dynamic_reconfigure
    roscpp
    rospy

)
#    ros_control
#    ros_controllers

generate_dynamic_reconfigure_options(
    cfg/ArmTeleop.cfg
)

catkin_package()

add_executable(rover_teleop src/Main.cpp src/ArmTeleop.cpp src/ArmJointsPublisher.cpp)
target_link_libraries(rover_teleop ${catkin_LIBRARIES})
add_dependencies(rover_teleop ${rover_simulation}_gencfg)
