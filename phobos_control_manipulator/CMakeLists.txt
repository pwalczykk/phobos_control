cmake_minimum_required(VERSION 2.8.3)
project(phobos_control_manipulator)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  dynamic_reconfigure
)

generate_dynamic_reconfigure_options(
  cfg/ManipParameters.cfg
  cfg/WheelsParam.cfg
  cfg/ControlMsgs.cfg
)

include_directories(${catkin_INCLUDE_DIRS} ${roscpp_INCLUDE_DIRS})

 add_message_files(
   FILES
   PositionOrientation.msg
 )

 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
   CATKIN_DEPENDS message_runtime
)

add_executable(reverse_kinematics
    src/reverse_kinematics/src/Main.cpp
    src/reverse_kinematics/src/PublisherFloat64.cpp
    src/reverse_kinematics/src/ReverseKinematicsCalculator.cpp)
target_link_libraries(reverse_kinematics ${catkin_LIBRARIES})


add_executable(manip_operation
    src/manip_operation/src/Main.cpp
    src/manip_operation/src/ManipGivenPosOriServer.cpp
    src/manip_operation/src/ManipGivenPosOriServerJoy.cpp)
target_link_libraries(manip_operation ${catkin_LIBRARIES})
add_dependencies( manip_operation ${phobos_manip_operation}_gencfg)


add_executable(wheel_control
    src/wheel_control/src/Main.cpp
    src/wheel_control/src/WheelJoyOp.cpp
    src/wheel_control/src/WheelKeyOp.cpp)
target_link_libraries(wheel_control ${catkin_LIBRARIES})
add_dependencies( wheel_control ${phobos_manip_operation}_gencfg)

add_executable(control_messages_interface
	src/control_messages_interface/src/Main.cpp
	src/control_messages_interface/src/PublisherInt16.cpp
	)

target_link_libraries(control_messages_interface ${catkin_LIBRARIES})
add_dependencies( control_messages_interface ${control_messages_interface}_gencfg)
