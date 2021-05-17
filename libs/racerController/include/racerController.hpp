#pragma once

#include "mechanicalValues.hpp"
#include "racer.hpp"
#include <optional>

#define DEFAULT_ROTATION_ACCELERATE 0.25
#define DEFAULT_SPEED_ACCELERATE 0.1
#define DEFAULT_MAX_SPEED 6
#define DEFAULT_MAX_ROTATION_SPEED 7
#define DEFAULT_EXTRA_VALUE 0
#define DEFAULT_NEW_POSITION                                                                                                                                   \
    { -1, -1 }
#define HAVE_NEW_POSITION(point) (point.x != -1 && point.y != -1)

class RacerController {
public:
    explicit RacerController(const float &rotAcc = DEFAULT_ROTATION_ACCELERATE, const float &speedAcc = DEFAULT_SPEED_ACCELERATE,
                             const float &maxSpeed = DEFAULT_MAX_SPEED, const float &maxRotationSpeed = DEFAULT_MAX_ROTATION_SPEED);
    void changeRotationSpeed(const Rotation &rotation, Racer &racer, const float &extraAccelerate = DEFAULT_EXTRA_VALUE) const;
    void changeSpeed(Racer &racer, const float &extraAccelerateX = DEFAULT_EXTRA_VALUE, const float &extraAccelerateY = DEFAULT_EXTRA_VALUE) const;

    void updateRotation(Racer &racer, const float &extraDegrees = 0);
    void updatePosition(Racer &racer, const Point &newCenterPosition = DEFAULT_NEW_POSITION);

private:
    float _rotationAccelerate;
    float _speedAccelerate;
    float _maxSpeed;
    float _maxRotationSpeed;

    float _previousRotation;

    void deceleratingSpeed(float &speed, const float &speedDecelerator) const;
};
