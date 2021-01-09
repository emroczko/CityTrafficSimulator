#pragma once
#include <SFML/Graphics.hpp>
#include "Vehicles/Truck.h"
#include "Vehicles/Car.h"

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

