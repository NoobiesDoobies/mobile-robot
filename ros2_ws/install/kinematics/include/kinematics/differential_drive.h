#ifndef DIFFERENTIAL_DRIVE_H
#define DIFFERENTIAL_DRIVE_H

class DifferentialDrive {
public:
    // Constructor
    DifferentialDrive();

    // // Destructor
    // ~DifferentialDrive();

    // Methods
    // void driveForward();
    // void driveBackward();
    // void turnLeft();
    // void turnRight();
    double* computeWheelVelocities(double vel_x, double vel_y, double angular_vel);

private:
    struct linearVelocity{
        double velocity_x;
        double velocity_y;
    };

    // Attributes
    linearVelocity linear_velocity_;
    double angular_velocity_;
    double wheel_radius_;
    double wheel_base_;
    double left_wheel_velocity_;
    double right_wheel_velocity_;
};

#endif // DIFFERENTIAL_DRIVE_H