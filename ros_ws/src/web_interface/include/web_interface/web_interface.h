#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

class WebInterface {
public:
    // Constructor
    WebInterface(ros::NodeHandle &nh);

    // Public member functions
    geometry_msgs::Twist getCmdTwist();
    

private:

    ros::NodeHandle nh_;
    // subscriber & publisher
    ros::Subscriber cmd_twist_sub_;

    // properties
    geometry_msgs::Twist cmd_twist_;

    // callback
    void cmdTwistCallback(const geometry_msgs::Twist::ConstPtr &msg);

};

#endif // WEB_INTERFACE_H