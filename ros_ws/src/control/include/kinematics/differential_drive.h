#ifndef DIFFERENTIAL_DRIVE_H
#define DIFFERENTIAL_DRIVE_H

class DifferentialDrive {
public:
    // Constructor
    DifferentialDrive(double wheelRadius, double wheelSeparation);  


    // // Methods
    double* getWheelVelocities(double linear, double angular);


private:
    // Member variables
    double wheelRadius_;
    double wheelSeparation_;
    
};

#endif  // DIFFERENTIAL_DRIVE_H