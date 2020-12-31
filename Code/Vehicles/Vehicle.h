#pragma once
#include "SFML/Graphics.hpp"

namespace ZPR {
	class Vehicle
	{
	public:
		virtual ~Vehicle() {};
		virtual void move() {};
		virtual sf::RectangleShape getShape();
		void updatePosition();
		int _x, _y, _speed;
		sf::RectangleShape _shape;
	};
}

