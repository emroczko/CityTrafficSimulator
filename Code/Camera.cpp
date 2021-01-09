#include "Camera.h"

namespace ZPR {
    Camera::Camera(int cameraNumber, sf::RectangleShape detectionBox) : _cameraNumber(cameraNumber), _cameraDetectionBox(detectionBox) {}

    bool Camera::CheckColision(std::shared_ptr<Vehicle> vehicle)
    {
        if (this->_cameraDetectionBox.getGlobalBounds().contains(vehicle->getShape().getPosition()) && vehicle->_seenByCamera == false) {
            return true;
        }
        else {
            return false;
        }
    }
}