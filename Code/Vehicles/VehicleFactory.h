#pragma once

#include "Vehicle.h"
#include <memory>
#include "Car.h"
#include "Truck.h"

namespace ZPR {
	class VehicleFactory
	{
	public:
		std::shared_ptr<Vehicle> CreateCar(int x, int y);
		std::shared_ptr<Vehicle> CreateTruck(int x, int y);
	};
}

