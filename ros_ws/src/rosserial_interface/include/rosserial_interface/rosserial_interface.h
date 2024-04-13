#ifndef rosserial_INTERFACE_H
#define rosserial_INTERFACE_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32MultiArray.h"

class RosserialInterface {
public:
    // Constructor
    RosserialInterface(ros::NodeHandle &nh);

    // Public member functions
    void publishWheelVelocities(double* wheel_velocities);
    

private:

    ros::NodeHandle nh_;
    // subscriber & publisher
    ros::Publisher wheel_vel_pub_;

    // properties

    // callback
    // void cmdTwistCallback(const geometry_msgs::Twist::ConstPtr &msg);

};

#endif // rosserial_INTERFACE_H