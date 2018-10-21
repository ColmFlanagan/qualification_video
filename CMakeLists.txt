cmake_minimum_required(VERSION 2.8.3)
project(qualification_video)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  rosplan_dispatch_msgs
  geometry_msgs
  visualization_msgs
)

add_service_files(

  FILES
  GoToMarker.srv
)
generate_messages(

  DEPENDENCIES
  geometry_msgs
  visualization_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES qualification_video
  CATKIN_DEPENDS roscpp rospy std_msgs rosplan_dispatch_msgs geometry_msgs visualization_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(plan_handler_node src/plan_handler src/plan_handler_node)
target_link_libraries(plan_handler_node
	${catkin_LIBRARIES}
)
add_dependencies(plan_handler_node 
	${PROJECT_NAME}_generate_message
)
