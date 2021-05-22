#include <cmath>
#include <functional>

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
        if (std::abs(racer._speed.speedX) > std::abs(_maxSpeed + std::copysignf(extraAccelerateX, _maxSpeed) * 4)) {
            if (racer._speed.speedX > _maxSpeed + extraAccelerateX * 4) {
                racer._speed.speedX -= decel;
            }
            if (racer._speed.speedX < (-_maxSpeed - extraAccelerateX * 4)) {
                racer._speed.speedX += decel;
            }
        } else {
            racer._speed.speedX += std::cos((racer._rotation * M_PI) / 180) * _speedAccelerate;
            racer._speed.speedX += extraAccelerateX;
        }

        if (std::abs(racer._speed.speedY) > std::abs(_maxSpeed + std::copysignf(extraAccelerateY, _maxSpeed) * 4)) {
            if (racer._speed.speedY > _maxSpeed + extraAccelerateY * 4) {
                racer._speed.speedY -= decel;
            }
            if (racer._speed.speedY < (-_maxSpeed - extraAccelerateY * 4)) {
                racer._speed.speedY += decel;
            }
        } else {
            racer._speed.speedY -= std::sin((racer._rotation * M_PI) / 180) * _speedAccelerate;
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

    auto rotatePointX = [&xCenter, &yCenter, &cosAlfa, sinAlfa](float x, float y) {
        return ((x - xCenter) * cosAlfa - (y - yCenter) * sinAlfa) + xCenter;
    };
    auto rotatePointY = [&xCenter, &yCenter, &cosAlfa, sinAlfa](float x, float y) {
        return ((x - xCenter) * sinAlfa + (y - yCenter) * cosAlfa) + yCenter;
    };

    racer._position.first.x = rotatePointX(x1Old, y1Old);  // top left
    racer._position.first.y = rotatePointY(x1Old, y1Old);
    racer._position.second.x = rotatePointX(x2Old, y2Old);  // bottom right
    racer._position.second.y = rotatePointY(x2Old, y2Old);
    racer._positionExtra.first.x = rotatePointX(x3Old, y3Old);  // bottom right
    racer._positionExtra.first.y = rotatePointY(x3Old, y3Old);
    racer._positionExtra.second.x = rotatePointX(x4Old, y4Old);  // top right
    racer._positionExtra.second.y = rotatePointY(x4Old, y4Old);

    _previousRotation = racer._rotation;
}

void RacerController::updatePosition(Racer &racer, const Point &newCenterPosition) {
    if (HAVE_NEW_POSITION(newCenterPosition)) {
        float deltaX = newCenterPosition.x - racer._center.x;
        float deltaY = newCenterPosition.y - racer._center.y;

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

//        racer._speed.speedX = -cosf((racer._rotation * M_PI) / 180) * _speedAccelerate * 10;
//        racer._speed.speedY = -sinf((racer._rotation * M_PI) / 180) * _speedAccelerate * 10;
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
