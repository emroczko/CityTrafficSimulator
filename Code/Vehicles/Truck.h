#pragma once

#include "SFML/Graphics.hpp"
#include "Vehicle.h"

namespace ZPR {
	class Truck : public Vehicle
	{
	public:
		Truck(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads);
	};

}
