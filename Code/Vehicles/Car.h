#pragma once
#include "SFML/Graphics.hpp"
#include "Vehicle.h"

namespace ZPR {
	class Car: public Vehicle
	{
	public:
		Car(int x, int y, int cllSize, std::vector<Cell> roads);
		sf::RectangleShape getShape();
	};
}
