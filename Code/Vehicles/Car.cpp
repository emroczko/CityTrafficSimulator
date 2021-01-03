#include "Car.h"
#include <iostream>
namespace ZPR {
	Car::Car(int x, int y) {
		this->_x = x;
		this->_y = y;
		_speed = 1;
		this->_direction = "South";
		this->_shape.setFillColor(sf::Color(255, 0, 0));
		this->_shape.setSize(sf::Vector2f(15, 15));
		this->_shape.setPosition(sf::Vector2f(x, y));
	}
	sf::RectangleShape Car::getShape()
	{
		return this->_shape;
	}
}
