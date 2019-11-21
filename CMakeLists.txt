cmake_minimum_required(VERSION 2.8.3)
project(cubot)
find_package(OpenCV QUIET)

find_package(catkin REQUIRED COMPONENTS
roscpp
rospy
std_msgs
image_transport 
cv_bridge
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cubot
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

if(OpenCV_FOUND)
    add_executable(cubot_cv_node src/cubot_cv_node.cpp)
    target_link_libraries(cubot_cv_node ${catkin_LIBRARIES})
    target_link_libraries(cubot_cv_node ${OpenCV_LIBS} ) 
endif(OpenCV_FOUND)
