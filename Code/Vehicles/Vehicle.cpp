#include "Vehicle.h"
namespace ZPR {
	sf::RectangleShape Vehicle::getShape()
	{
		return this->_shape;
	}
	void Vehicle::move()
	{
		if (_direction == "North") {
			this->_y -= this->_speed;
		}
		else if (_direction == "South") {
			this->_y += this->_speed;
		}
		else if (_direction == "East") {
			this->_x += this->_speed;
		}
		else if (_direction == "West") {
			this->_x -= this->_speed;
		}
		updatePosition();
	}
	void Vehicle::updatePosition() {
		this->_shape.setPosition(sf::Vector2f(_x, _y));
	}
	void Vehicle::updateDirection(std::string direction)
	{
		this->_direction = direction;
	}
}
