#pragma once

#include "SFML/Graphics.hpp"
#include "Vehicle.h"

namespace ZPR {
	class Truck : public Vehicle
	{
	public:
		Truck(int x, int y);
		sf::RectangleShape getShape();
	};

}