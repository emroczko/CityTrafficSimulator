#pragma once
#include <SFML/Graphics.hpp>
#include "Vehicles/truck.hpp"
#include "Vehicles/car.hpp"

namespace ZPR {
	class Camera
	{
	public:
		Camera(int cameraNumber, sf::RectangleShape detectionBox);
		bool CheckColision(std::shared_ptr<Vehicle> vehicle);
		int _cameraNumber;
	private:
		sf::RectangleShape _cameraDetectionBox;
	};
}

