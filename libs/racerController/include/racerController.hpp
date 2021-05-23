#pragma once

#include "mechanicalValues.hpp"
#include "racer.hpp"
#include <optional>

constexpr float DEFAULT_ROTATION_ACCELERATE = 0.09;
constexpr float DEFAULT_SPEED_ACCELERATE = 0.03;
constexpr float DEFAULT_MAX_SPEED = 2.2;
constexpr float DEFAULT_MAX_ROTATION_SPEED = 4;
constexpr float DEFAULT_EXTRA_VALUE = 0;
constexpr float CRITICAL_SPEED = 10;
#define DEFAULT_NEW_POSITION                                                                                                                                   \
    { -1, -1 }
#define HAVE_NEW_POSITION(point) ((point).x != -1 && (point).y != -1)

class RacerController {
public:
    explicit RacerController(const float &rotAcc = DEFAULT_ROTATION_ACCELERATE, const float &speedAcc = DEFAULT_SPEED_ACCELERATE,
                             const float &maxSpeed = DEFAULT_MAX_SPEED, const float &maxRotationSpeed = DEFAULT_MAX_ROTATION_SPEED);
    void changeRotationSpeed(const Command &rotation, Racer &racer, const float &extraAccelerate = DEFAULT_EXTRA_VALUE) const;
    void changeSpeed(Racer &racer, bool stop = false, const float &extraAccelerateX = DEFAULT_EXTRA_VALUE, const float &extraAccelerateY = DEFAULT_EXTRA_VALUE);

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
