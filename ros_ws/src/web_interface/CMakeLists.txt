cmake_minimum_required(VERSION 3.0.2)
project(web_interface)

find_package(catkin REQUIRED COMPONENTS
  # find other package needed to build
  geometry_msgs
  roscpp
  std_msgs
)

catkin_package(
  # specify package build info export
 INCLUDE_DIRS include
 LIBRARIES ${PROJECT_NAME}
 CATKIN_DEPENDS geometry_msgs roscpp std_msgs nav_msgs
)

include_directories(
  # include your own package's include directory to make sure the compiler find them
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(
  # libraries to build
  ${PROJECT_NAME}
  src/${PROJECT_NAME}/web_interface.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/web_interface   # Add this line
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
