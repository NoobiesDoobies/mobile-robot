#include "rosserial_interface/rosserial_interface.h"

RosserialInterface::RosserialInterface(ros::NodeHandle &nh) : nh_(nh)
{
    // initialize publisher
    wheel_vel_pub_ = nh_.advertise<std_msgs::Float32MultiArray>("/wheel_vel_cmd", 1);
}

void RosserialInterface::publishWheelVelocities(double* wheel_velocities)
{
    // create message
    std_msgs::Float32MultiArray msg;
    msg.data.clear();
    for (int i = 0; i < 2; i++)
    {
        msg.data.push_back(wheel_velocities[i]);
    }

    // publish message
    wheel_vel_pub_.publish(msg);
}