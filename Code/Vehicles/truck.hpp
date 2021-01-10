#pragma once

#include "SFML/Graphics.hpp"
#include "vehicle.hpp"

namespace zpr {
	class Truck : public Vehicle
	{
	public:
		Truck(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads);
	};

}
