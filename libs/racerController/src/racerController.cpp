#include <cmath>

#include "racerController.hpp"

void RacerController::changeRotationSpeed(const Rotation &_rotation, Racer &racer, const float &extraAccelerate) const {  // SpeedX - left; SpeedY - right
    switch (_rotation) {
        case left:
            if (racer._rotationSpeed.speedX < _maxRotationSpeed + extraAccelerate * 2) {
                racer._rotationSpeed.speedX += _rotationAccelerate + extraAccelerate;
            }
            deceleratingSpeed(racer._rotationSpeed.speedY, _rotationAccelerate);
            break;
        case right:
            if (racer._rotationSpeed.speedY < _maxRotationSpeed + extraAccelerate * 2) {
                racer._rotationSpeed.speedY += _rotationAccelerate + extraAccelerate;
            }
            deceleratingSpeed(racer._rotationSpeed.speedX, _rotationAccelerate);
            break;
        case none:
            deceleratingSpeed(racer._rotationSpeed.speedX, _rotationAccelerate);
            deceleratingSpeed(racer._rotationSpeed.speedY, _rotationAccelerate);
            break;
    }
}

void RacerController::changeSpeed(Racer &racer, bool stop, const float &extraAccelerateX, const float &extraAccelerateY) {
    if (!stop) {
        float decel = _speedAccelerate / 10;
//        if (racer._speed.speedX > _maxSpeed + extraAccelerateX * 10 || racer._speed.speedX < -_maxSpeed - extraAccelerateX * 10) {
        if (std::abs(racer._speed.speedX) > std::abs(_maxSpeed + std::copysignf(extraAccelerateX, _maxSpeed) * 10)) {
            if (racer._speed.speedX > _maxSpeed + extraAccelerateX * 10) {
                racer._speed.speedX -= decel;
            }
            if (racer._speed.speedX < (-_maxSpeed - extraAccelerateX * 10)) {
                racer._speed.speedX += decel;
            }
        } else {
            racer._speed.speedX += cosf((racer._rotation * M_PI) / 180) * _speedAccelerate;
            racer._speed.speedX += extraAccelerateX;
        }

        if (std::abs(racer._speed.speedY) > std::abs(_maxSpeed + std::copysignf(extraAccelerateY, _maxSpeed) * 10)) {
            if (racer._speed.speedY > _maxSpeed + extraAccelerateY * 10) {
                racer._speed.speedY -= decel;
            }
            if (racer._speed.speedY < (-_maxSpeed - extraAccelerateY * 10)) {
                racer._speed.speedY += decel;
            }
        } else {
            racer._speed.speedY -= sinf((racer._rotation * M_PI) / 180) * _speedAccelerate;
            racer._speed.speedY += extraAccelerateY;
        }

        deceleratingSpeed(racer._speed.speedX, std::abs(_speedAccelerate * racer._speed.speedX / 15));
        deceleratingSpeed(racer._speed.speedY, std::abs(_speedAccelerate * racer._speed.speedY / 15));
    } else {
        racer._speed.speedX = -cosf((racer._rotation * M_PI) / 180) * _speedAccelerate * 10;
        racer._speed.speedY = -sinf((racer._rotation * M_PI) / 180) * _speedAccelerate * 10;
    }
}

void RacerController::updateRotation(Racer &racer, const float &extraDegrees) {
    racer._rotation += racer._rotationSpeed.speedX - racer._rotationSpeed.speedY + extraDegrees;

    float addingRotation = racer._rotation - _previousRotation;

    float x1Old = racer._position.first.x;  // top left
    float y1Old = racer._position.first.y;
    float x2Old = racer._position.second.x;  // bottom right
    float y2Old = racer._position.second.y;
    float x3Old = racer._positionExtra.first.x;  // bottom left
    float y3Old = racer._positionExtra.first.y;
    float x4Old = racer._positionExtra.second.x;  // top right
    float y4Old = racer._positionExtra.second.y;

    float xCenter = racer._center.x;
    float yCenter = racer._center.y;

    float cosAlfa = cosf(-addingRotation * (M_PI / 180));
    float sinAlfa = sinf(-addingRotation * (M_PI / 180));

    racer._position.first.x = ((x1Old - xCenter) * cosAlfa - (y1Old - yCenter) * sinAlfa) + xCenter;  // top left
    racer._position.first.y = ((x1Old - xCenter) * sinAlfa + (y1Old - yCenter) * cosAlfa) + yCenter;
    racer._position.second.x = ((x2Old - xCenter) * cosAlfa - (y2Old - yCenter) * sinAlfa) + xCenter;  // bottom right
    racer._position.second.y = ((x2Old - xCenter) * sinAlfa + (y2Old - yCenter) * cosAlfa) + yCenter;
    racer._positionExtra.first.x = ((x3Old - xCenter) * cosAlfa - (y3Old - yCenter) * sinAlfa) + xCenter;  // bottom right
    racer._positionExtra.first.y = ((x3Old - xCenter) * sinAlfa + (y3Old - yCenter) * cosAlfa) + yCenter;
    racer._positionExtra.second.x = ((x4Old - xCenter) * cosAlfa - (y4Old - yCenter) * sinAlfa) + xCenter;  // top right
    racer._positionExtra.second.y = ((x4Old - xCenter) * sinAlfa + (y4Old - yCenter) * cosAlfa) + yCenter;

    _previousRotation = racer._rotation;
}

void RacerController::updatePosition(Racer &racer, const Point &newCenterPosition) {
    if (HAVE_NEW_POSITION(newCenterPosition)) {
        float deltaX = racer._center.x - newCenterPosition.x;
        float deltaY = racer._center.y - newCenterPosition.y;

        racer._center.x = newCenterPosition.x;
        racer._center.y = newCenterPosition.y;
        racer._position.first.x += deltaX;
        racer._position.first.y += deltaY;
        racer._position.second.x += deltaX;
        racer._position.second.y += deltaY;
        racer._positionExtra.first.x += deltaX;
        racer._positionExtra.first.y += deltaY;
        racer._positionExtra.second.x += deltaX;
        racer._positionExtra.second.y += deltaY;

        racer._speed.speedX = -cosf((racer._rotation * M_PI) / 180) * _speedAccelerate * 10;
        racer._speed.speedY = -sinf((racer._rotation * M_PI) / 180) * _speedAccelerate * 10;
    } else {
        racer._position.first.x += racer._speed.speedX;
        racer._position.first.y += racer._speed.speedY;
        racer._position.second.x += racer._speed.speedX;
        racer._position.second.y += racer._speed.speedY;
        racer._positionExtra.first.x += racer._speed.speedX;
        racer._positionExtra.first.y += racer._speed.speedY;
        racer._positionExtra.second.x += racer._speed.speedX;
        racer._positionExtra.second.y += racer._speed.speedY;
        racer._center.x += racer._speed.speedX;
        racer._center.y += racer._speed.speedY;
    }
}

RacerController::RacerController(const float &rotAcc, const float &speedAcc, const float &maxSpeed, const float &maxRotationSpeed)
    : _rotationAccelerate(rotAcc)
    , _speedAccelerate(speedAcc)
    , _maxSpeed(maxSpeed)
    , _maxRotationSpeed(maxRotationSpeed)
    , _previousRotation(0) {}

void RacerController::deceleratingSpeed(float &speed, const float &speedDecelerator) const {
    if (speed > 0) {
        if (speed - speedDecelerator <= 0) {
            speed = 0;
        } else {
            speed -= speedDecelerator;
        }
    } else if (speed < 0) {
        if (speed + speedDecelerator >= 0) {
            speed = 0;
        } else {
            speed += speedDecelerator;
        }
    }
}
