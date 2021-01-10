/**
 * truck.hpp
 * Header of Truck class.
 */

#pragma once

#include "SFML/Graphics.hpp"
#include "vehicle.hpp"

namespace zpr {

    /**
     * Class responsible for being a truck in the simulation, inherited from Vehicle.
     */
	class Truck : public Vehicle
	{
	public:
		Truck(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads);
	};

}
