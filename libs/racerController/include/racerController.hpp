#pragma once

#include <mechanicalValues.hpp>
#include <racer.hpp>

class RacerController {
public:
    explicit RacerController(const double &rotAcc = 0.15, const double &speedAcc = 0.1, const double &maxSpeed = 4.5, const double &maxRotationSpeed = 4.5);
    void changeRotation(const Rotation &rotation, Racer &racer, double extraAccelerate = 0) const;
    void update(Racer &racer) const;

private:
    double _rotationAccelerate;
    double _speedAccelerate;
    double _maxSpeed;
    double _maxRotationSpeed;
};
