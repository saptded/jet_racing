#pragma once

#include "mechanicalValues.hpp"
#include "racer.hpp"
#include <optional>

#define DEFAULT_ROTATION_ACCELERATE 0.1
#define DEFAULT_SPEED_ACCELERATE 0.1
#define DEFAULT_MAX_SPEED 4
#define DEFAULT_MAX_ROTATION_SPEED 7
#define DEFAULT_EXTRA_VALUE 0
#define DEFAULT_NEW_POSITION {-1, -1}
#define HAVE_NEW_POSITION(point)(point.x != -1 && point.y != -1)

class RacerController {
public:
    explicit RacerController(const double &rotAcc = DEFAULT_ROTATION_ACCELERATE, const double &speedAcc = DEFAULT_SPEED_ACCELERATE,
                             const double &maxSpeed = DEFAULT_MAX_SPEED, const double &maxRotationSpeed = DEFAULT_MAX_ROTATION_SPEED);
    void changeRotationSpeed(const Rotation &rotation, Racer &racer, const double &extraAccelerate = DEFAULT_EXTRA_VALUE) const;
    void changeSpeed(Racer &racer, const double &extraAccelerate = DEFAULT_EXTRA_VALUE) const;

    void updateRotation(Racer &racer, const double &extraDegrees = 0);
    void updatePosition(Racer &racer, const Point &newCenterPosition = DEFAULT_NEW_POSITION);

private:
    double _rotationAccelerate;
    double _speedAccelerate;
    double _maxSpeed;
    double _maxRotationSpeed;
};
