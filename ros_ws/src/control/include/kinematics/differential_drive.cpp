#include "kinematics/differential_drive.h"

DifferentialDrive::DifferentialDrive(double wheelRadius, double wheelSeparation) : wheelRadius_(wheelRadius),
                                                                                   wheelSeparation_(wheelSeparation)
{
}

double *DifferentialDrive::getWheelVelocities(double linear, double angular)
{
    static double wheelVelocities[2];
    wheelVelocities[0] = (2 * linear - angular * wheelSeparation_) / (2 * wheelRadius_);

    wheelVelocities[1] = (2 * linear + angular * wheelSeparation_) / (2 * wheelRadius_);

    return wheelVelocities;
}

