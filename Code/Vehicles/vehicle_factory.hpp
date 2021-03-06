/**
 * vehicle_factory.hpp
 * Header of VehicleFactory class.
 */
#pragma once
#include <memory>
#include "car.hpp"
#include "truck.hpp"

namespace zpr {

    /**
     * Class responsible for being a vehicle factory. It creates cars and trucks.
     */
	class VehicleFactory
	{
	public:
		static std::shared_ptr<Vehicle> createCar(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads, std::string direction);
		static std::shared_ptr<Vehicle> createTruck(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads, std::string direction);
	};
}

