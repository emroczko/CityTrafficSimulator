#include "camera.hpp"

namespace zpr {
    Camera::Camera(int camera_number, sf::RectangleShape detection_box) : cameraNumber_(camera_number), cameraDetectionBox_(detection_box) {}

    bool Camera::checkColision(std::shared_ptr<Vehicle> vehicle)
    {
        if (this->cameraDetectionBox_.getGlobalBounds().contains(vehicle->getShape().getPosition())) {
            return true;
        }
        else {
            return false;
        }
    }
}
