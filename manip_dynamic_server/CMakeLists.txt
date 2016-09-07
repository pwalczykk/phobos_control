cmake_minimum_required(VERSION 2.8.3)
project(phobos_control_manipulator)

find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  roscpp
  rospy
)

generate_dynamic_reconfigure_options(
  cfg/ManipParameters.cfg
  cfg/WheelsParam.cfg
)

#add_dependencies( phobos_control_manipulator ${PROJECT_NAME}_gencfg)
