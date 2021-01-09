#pragma once
#include "SFML/Graphics.hpp"
#include "vehicle.hpp"

namespace ZPR {
	class Car: public Vehicle
	{
	public:
		Car(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads);
	};
}
