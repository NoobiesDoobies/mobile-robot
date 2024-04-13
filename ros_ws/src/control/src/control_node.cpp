#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#include "kinematics/differential_drive.h"

#include "web_interface/web_interface.h"
#include "rosserial_interface/rosserial_interface.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "control_node");
    ros::NodeHandle nh = ros::NodeHandle("~");
    WebInterface web_interface(nh);
    RosserialInterface rosserial_interface(nh);

    double wheelRadius = 0.1;
    double wheelSeparation = 0.5;

    DifferentialDrive differential_drive(wheelRadius, wheelSeparation);
    ros::Rate rate(10);

    while (ros::ok())
    {
        ros::spinOnce();
        geometry_msgs::Twist twist = web_interface.getCmdTwist();
        double *wheelVelocities;
        wheelVelocities = differential_drive.getWheelVelocities(twist.linear.x, twist.angular.z);
        ROS_INFO("Left wheel velocity: %f, Right wheel velocity: %f", wheelVelocities[0], wheelVelocities[1]);
        rosserial_interface.publishWheelVelocities(wheelVelocities);
        rate.sleep();
    }
}
