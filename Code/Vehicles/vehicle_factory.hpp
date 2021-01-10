
#pragma once
#include "vehicle.hpp"
#include <memory>
#include "car.hpp"
#include "truck.hpp"

namespace zpr {
	class VehicleFactory
	{
	public:
		static std::shared_ptr<Vehicle> createCar(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads);
		static std::shared_ptr<Vehicle> createTruck(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads);
	};
}

