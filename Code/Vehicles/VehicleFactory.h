#pragma once

#include "Vehicle.h"
#include <memory>
#include "Car.h"
#include "Truck.h"

namespace ZPR {
	class VehicleFactory
	{
	public:
		static std::shared_ptr<Vehicle> CreateCar(int x, int y, int cellSize, std::vector<Cell> roads);	//std::vector<Cell> roads);
		static std::shared_ptr<Vehicle> CreateTruck(int x, int y, int cellSize, std::vector<Cell> roads);	//std::vector<Cell> roads);
	};
}

