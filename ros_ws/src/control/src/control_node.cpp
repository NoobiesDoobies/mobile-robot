#include "ros/ros.h"


void mainLoop(const::ros::TimerEvent&);

int main(int argc, char **argv){
    ros::init(argc, argv, "control_node");
    ros::NodeHandle nh = ros::NodeHandle("~");

    ros::Timer timer = nh.createTimer(ros::Duration(1.0), mainLoop);

    ros::spin();

}

void mainLoop(const::ros::TimerEvent&){
    ROS_INFO("Control node is running");
}