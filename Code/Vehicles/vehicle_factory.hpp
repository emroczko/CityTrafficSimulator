#pragma once
#include "vehicle.hpp"
#include <memory>
#include "car.hpp"
#include "truck.hpp"

namespace ZPR {
	class VehicleFactory
	{
	public:
		static std::shared_ptr<Vehicle> CreateCar(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads);	//std::vector<Cell> roads);
		static std::shared_ptr<Vehicle> CreateTruck(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads);	//std::vector<Cell> roads);
	};
}

