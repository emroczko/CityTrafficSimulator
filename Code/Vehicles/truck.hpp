#pragma once

#include "SFML/Graphics.hpp"
#include "vehicle.hpp"

namespace ZPR {
	class Truck : public Vehicle
	{
	public:
		Truck(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads);
	};

}
