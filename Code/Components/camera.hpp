/**
 * camera.hpp
 * Header of Camera class.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "../Vehicles/truck.hpp"
#include "../Vehicles/car.hpp"

namespace zpr {

    /**
     * Class responsible for being a camera and handle its actions.
     */
	class Camera
	{
	public:
		Camera(int camera_number, sf::RectangleShape detection_box);
		bool checkColision(std::shared_ptr<Vehicle> vehicle);
		int cameraNumber_;
	private:
		sf::RectangleShape cameraDetectionBox_;
	};
}

