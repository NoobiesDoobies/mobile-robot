#include "web_interface/web_interface.h"

WebInterface::WebInterface(ros::NodeHandle &nh) : nh_(nh)
{
    // initialize subscriber
    cmd_twist_sub_ = nh_.subscribe("/cmd_twist", 1, &WebInterface::cmdTwistCallback, this);
}

void WebInterface::cmdTwistCallback(const geometry_msgs::Twist::ConstPtr &msg)
{
    cmd_twist_ = *msg;
}

geometry_msgs::Twist WebInterface::getCmdTwist()
{
    return cmd_twist_;
}