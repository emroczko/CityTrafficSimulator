#include "Car.h"
#include <iostream>
namespace ZPR {
	Car::Car(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads) {
		this->_x = x;
		this->_y = y;
		_speed = 1;
        this->_roads = roads;
		this->_cellSize = cellSize;
		this->_direction = "South";
		this->_shape.setFillColor(sf::Color(255, 0, 0));
		this->_shape.setSize(sf::Vector2f(15 * cellSize / ROAD_IMAGE_SIZE, 15 * cellSize / ROAD_IMAGE_SIZE));
		this->_shape.setPosition(sf::Vector2f(x, y));
	}
	sf::RectangleShape Car::getShape()
	{
		return this->_shape;
	}
}
