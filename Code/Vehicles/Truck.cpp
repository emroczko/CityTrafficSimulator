#include "Truck.h"
namespace ZPR {
	Truck::Truck(int x, int y) {
		this->_x = x;
		this->_y = y;
		_speed = 1;
		this->_direction = "South";
		this->_shape.setFillColor(sf::Color(0, 0, 255));
		this->_shape.setSize(sf::Vector2f(15, 20));
		this->_shape.setPosition(sf::Vector2f(x, y));
		
	}
	sf::RectangleShape Truck::getShape()
	{
		return this->_shape;
	}
}
