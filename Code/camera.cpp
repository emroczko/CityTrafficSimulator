#include "camera.hpp"

namespace ZPR {
    Camera::Camera(int cameraNumber, sf::RectangleShape detectionBox) : _cameraNumber(cameraNumber), _cameraDetectionBox(detectionBox) {}

    bool Camera::CheckColision(std::shared_ptr<Vehicle> vehicle)
    {
        if (this->_cameraDetectionBox.getGlobalBounds().contains(vehicle->getShape().getPosition())) {
            return true;
        }
        else {
            return false;
        }
    }
}
