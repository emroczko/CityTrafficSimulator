/**
 * camera.cpp
 * Implementation of Camera class.
 */
#include "camera.hpp"

namespace zpr {

    /**
     * Parametrized constructor of Camera class.
     * @param camera_number - Camera number.
     * @param detection_box - Area which camera sees.
     */
    Camera::Camera(int camera_number, sf::RectangleShape detection_box) : cameraNumber_(camera_number), cameraDetectionBox_(detection_box) {}

    /**
     * Method which checks if a vehicle is visible for camera.
     * @param vehicle - Vehicle which method is checking.
     * @return - True if camera detects vehicle, false otherwise.
     */
    bool Camera::checkColision(std::shared_ptr<Vehicle> vehicle)
    {
        if(this->cameraDetectionBox_.getGlobalBounds().contains(vehicle->getShape().getPosition())) {
            return true;
        }
        else {
            return false;
        }
    }
}
