#pragma once

#include "Vehicle.h"
#include <memory>
#include "Car.h"
#include "Truck.h"

namespace ZPR {
	class VehicleFactory
	{
	public:
		static std::shared_ptr<Vehicle> CreateCar(int x, int y);
		static std::shared_ptr<Vehicle> CreateTruck(int x, int y);
	};
}

