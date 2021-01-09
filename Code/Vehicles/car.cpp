#include "car.hpp"
#include <iostream>
namespace ZPR {
	Car::Car(int x, int y, int cellSize, std::vector<sf::RectangleShape> roads) {
		this->_x = x;
		this->_y = y;
		_speed = 3;
        this->_roads = roads;
		this->_cellSize = cellSize;
		this->_seenByCamera = false;
		this->_sidewalkSize = round(SIDEWALK_SIZE * _cellSize / ROAD_IMAGE_SIZE);
		this->_roadSize = round(ROAD_SIZE * _cellSize / ROAD_IMAGE_SIZE);
		this->_roadStripesSize = round(ROAD_STRIPES_SIZE * _cellSize / ROAD_IMAGE_SIZE);
		this->_direction = "South";
		this->_previousDirection = "";
		this->_currentRoad = nullptr;
		this->_previousRoad = nullptr;
		this->_shape.setFillColor(sf::Color(255, 0, 0));
		this->_shape.setSize(sf::Vector2f(14 * cellSize / ROAD_IMAGE_SIZE, 14 * cellSize / ROAD_IMAGE_SIZE));
		this->_shape.setOrigin(this->_shape.getSize().x / 2, this->_shape.getSize().y / 2);
		this->_shape.setPosition(sf::Vector2f(x, y));
		this->_colisionBox.setFillColor(sf::Color::Yellow);
		this->_colisionBox.setSize(sf::Vector2f(round(14 * cellSize / ROAD_IMAGE_SIZE), round(14 * cellSize / ROAD_IMAGE_SIZE)));
		this->_colisionBox.setOrigin(this->_colisionBox.getSize().x / 2, this->_colisionBox.getSize().y / 2);
		this->_colisionBox.setPosition(sf::Vector2f(this->_shape.getPosition().x, this->_shape.getPosition().y + (this->_colisionBox.getSize().y / 2 + this->_shape.getSize().y / 2 + this->_roadStripesSize)));
	}
}
