#include "Vehicle.h"
namespace ZPR {
	sf::RectangleShape Vehicle::getShape()
	{
		return this->_shape;
	}
	void Vehicle::updatePosition() {
		this->_shape.setPosition(sf::Vector2f(_x, _y));
	}
}
