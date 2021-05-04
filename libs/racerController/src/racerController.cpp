#include <cmath>

#include "racerController.hpp"

void RacerController::changeRotationSpeed(const Rotation &_rotation, Racer &racer, const double &extraAccelerate) const {  // SpeedX - left; SpeedY - right
    switch (_rotation) {
        case left:
            //            if (racer._rotationSpeed.speedY > _maxRotationSpeed - 3) {
            //                racer._rotationSpeed.speedY = 2;
            //            }
            if (racer._rotationSpeed.speedX < _maxRotationSpeed + extraAccelerate * 2) {
                racer._rotationSpeed.speedX += _rotationAccelerate + extraAccelerate;

                if (racer._rotationSpeed.speedY >= 0) {
                    racer._rotationSpeed.speedY -= _rotationAccelerate + extraAccelerate;
                }
            }
            break;
        case right:
            //            if (racer._rotationSpeed.speedX > _maxRotationSpeed - 3) {
            //                racer._rotationSpeed.speedX = 2;
            //            }
            if (racer._rotationSpeed.speedY < _maxRotationSpeed + extraAccelerate * 2) {
                racer._rotationSpeed.speedY += _rotationAccelerate + extraAccelerate;
                if (racer._rotationSpeed.speedX >= 0) {

                    racer._rotationSpeed.speedX -= _rotationAccelerate;
                }
            }
            break;
        case none:

            if (racer._rotationSpeed.speedX >= _rotationAccelerate) {
                racer._rotationSpeed.speedX -= _rotationAccelerate;
            }
            if (racer._rotationSpeed.speedY >= _rotationAccelerate) {
                racer._rotationSpeed.speedY -= _rotationAccelerate;
            }
            break;
    }
}

void RacerController::changeSpeed(Racer &racer, const double &extraAccelerate) const {
    racer._speed.speedX += cos((racer._rotation * M_PI) / 180) * (_speedAccelerate + extraAccelerate);

    if (racer._speed.speedX > _maxSpeed) {
        racer._speed.speedX -= _speedAccelerate;
    }
    if (racer._speed.speedX < (-_maxSpeed)) {
        racer._speed.speedX += _speedAccelerate;
    }

    racer._speed.speedY -= sin((racer._rotation * M_PI) / 180) * (_speedAccelerate + extraAccelerate);

    if (racer._speed.speedY > _maxSpeed) {
        racer._speed.speedY -= _speedAccelerate;
    }
    if (racer._speed.speedY < (-_maxSpeed)) {
        racer._speed.speedY += _speedAccelerate;
    }
}

void RacerController::updateRotation(Racer &racer, const double &extraDegrees) {
    racer._rotation += racer._rotationSpeed.speedX - racer._rotationSpeed.speedY + extraDegrees;

    double x1Old = racer._position.first.x;
    double y1Old = racer._position.first.y;
    double x2Old = racer._position.second.x;
    double y2Old = racer._position.second.y;

    double xCenter = racer._center.x;
    double yCenter = racer._center.y;

    double cosAlfa = cos(racer._rotation * (M_PI / 180));
    double sinAlfa = sin(racer._rotation * (M_PI / 180));

    racer._position.first.x = ((x1Old - xCenter) * cosAlfa - (y1Old - yCenter) * sinAlfa) + xCenter;
    racer._position.first.y = ((x1Old - xCenter) * sinAlfa + (y1Old - yCenter) * cosAlfa) + yCenter;
    racer._position.second.x = ((x2Old - xCenter) * cosAlfa - (y2Old - yCenter) * sinAlfa) + xCenter;
    racer._position.second.y = ((x2Old - xCenter) * sinAlfa + (y2Old - yCenter) * cosAlfa) + yCenter;
}

void RacerController::updatePosition(Racer &racer, const Point &newCenterPosition) {
    if (HAVE_NEW_POSITION(newCenterPosition)) {
        double deltaX = racer._center.x - newCenterPosition.x;
        double deltaY = racer._center.y - newCenterPosition.y;

        racer._center.x = newCenterPosition.x;
        racer._center.y = newCenterPosition.y;

        racer._position.first.x += deltaX;
        racer._position.first.y += deltaY;
        racer._position.second.x += deltaX;
        racer._position.second.y += deltaY;

        racer._speed.speedX = 0;
        racer._speed.speedY = 0;
    } else {
        racer._position.first.x += racer._speed.speedX;
        racer._position.first.y += racer._speed.speedY;
        racer._position.second.x += racer._speed.speedX;
        racer._position.second.y += racer._speed.speedY;

        racer._center.x += racer._speed.speedX;
        racer._center.y += racer._speed.speedY;
    }
}

RacerController::RacerController(const double &rotAcc, const double &speedAcc, const double &maxSpeed, const double &maxRotationSpeed)
    : _rotationAccelerate(rotAcc)
    , _speedAccelerate(speedAcc)
    , _maxSpeed(maxSpeed)
    , _maxRotationSpeed(maxRotationSpeed) {}
