#pragma once
#include "SFML/Graphics.hpp"

namespace ZPR {
	class Vehicle : public sf::Drawable
	{
	public:
		virtual ~Vehicle() {};
		virtual sf::RectangleShape getShape();
		void move();
		void updatePosition();
		void updateDirection(std::string direction);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		int _x, _y, _speed;
		std::string _direction;
		sf::RectangleShape _shape;
	};
}

