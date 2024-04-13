cmake_minimum_required(VERSION 3.0.2)
project(control)

find_package(catkin REQUIRED
    roscpp
    std_msgs
    geometry_msgs
    web_interface
    rosserial_interface
)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES kinematics
 CATKIN_DEPENDS roscpp std_msgs geometry_msgs web_interface rosserial_interface
)
include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

add_library(
    kinematics
    include/kinematics/differential_drive.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/kinematics   # Add this line

)

add_executable(${PROJECT_NAME}_node src/control_node.cpp)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
    kinematics
)


install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
