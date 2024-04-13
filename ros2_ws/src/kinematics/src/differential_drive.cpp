#include "kinematics/differential_drive.h"

// Implement the member functions of the DifferentialDrive class here
DifferentialDrive::DifferentialDrive()
{
    linear_velocity_.velocity_x = 0.0;
    linear_velocity_.velocity_y = 0.0;
    angular_velocity_ = 0.0;
    wheel_radius_ = 5.0;
    wheel_base_ = 0.0;
    left_wheel_velocity_ = 0.0;
    right_wheel_velocity_ = 0.0;
}

double* DifferentialDrive::computeWheelVelocities(double vel_x, double vel_y, double angular_vel){
    // Compute the linear velocity
    linear_velocity_.velocity_x = vel_x;
    linear_velocity_.velocity_y = vel_y;


    // Compute the angular velocity
    angular_velocity_ = angular_vel;

    // Compute the left and right wheel velocities
    left_wheel_velocity_ = (linear_velocity_.velocity_x - angular_velocity_ * wheel_base_ / 2) / wheel_radius_;
    right_wheel_velocity_ = (linear_velocity_.velocity_x + angular_velocity_ * wheel_base_ / 2) / wheel_radius_;

    static double wheel_velocity[2];
    wheel_velocity[0] = left_wheel_velocity_;
    wheel_velocity[1] = right_wheel_velocity_;
    return wheel_velocity;
}