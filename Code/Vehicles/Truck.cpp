#include "Truck.h"
namespace ZPR {
	Truck::Truck(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads) {
		this->_x = x;
		this->_y = y;
		_speed = 1;
		this->_roads = roads;
		this->_cellSize = cellSize;
		this->_direction = "South";
		this->_shape.setFillColor(sf::Color(0, 0, 255));
        this->_shape.setSize(sf::Vector2f(round(15 * cellSize/ROAD_IMAGE_SIZE), round(20 * cellSize / ROAD_IMAGE_SIZE)));
		this->_shape.setPosition(sf::Vector2f(x, y));
	}
	sf::RectangleShape Truck::getShape()
	{
		return this->_shape;
	}
}
