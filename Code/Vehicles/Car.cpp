#include "Car.h"
#include <iostream>
namespace ZPR {
	Car::Car(int x, int y) {
		this->_x = x;
		this->_y = y;
		_speed = 1;
		this->_shape.setFillColor(sf::Color(255, 0, 0));
		this->_shape.setSize(sf::Vector2f(15, 15));
		this->_shape.setPosition(sf::Vector2f(x, y));
	}

	void Car::move() {
		srand((unsigned)time(NULL));
		switch (rand() % 4)
		{
		case 0: _x += _speed; break;
		case 1: _x -= _speed; break;
		case 2: _y += _speed; break;
		case 3: _y -= _speed; break;
		}
		if (_x > 1200)
		{
			_x = 1100;
		}
		if (_y > 800)
		{
			_y = 700;
		}
		if (_x < 0)
		{
			_x < 0;
		}
		if (_y < 0)
		{
			_y = 0;
		}
		updatePosition();
	}
	sf::RectangleShape Car::getShape()
	{
		return this->_shape;
	}
}
