cmake_minimum_required(VERSION 2.8.3)
project(rover_rqt_teleop)

find_package(catkin REQUIRED COMPONENTS
    dynamic_reconfigure
    roscpp
    rospy

)

generate_dynamic_reconfigure_options(
    cfg/ArmTeleop.cfg
)

catkin_package()

add_executable(rover_rqt_teleop src/Main.cpp src/ArmTeleop.cpp src/ArmJointsPublisher.cpp)
target_link_libraries(rover_rqt_teleop ${catkin_LIBRARIES})
add_dependencies(rover_rqt_teleop ${rover_rqt_teleop}_gencfg)
