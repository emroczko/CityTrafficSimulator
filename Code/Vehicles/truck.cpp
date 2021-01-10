/**
 * truck.cpp
 * Implementation of Truck class.
 */

#include "truck.hpp"

namespace zpr {

    /**
     * Parametrized constructor of Truck class.
     * @param x - Position x of the truck.
     * @param y - Position y of the truck.
     * @param cell_size - Size of a cell.
     * @param roads - Vector of available roads.
     */
	Truck::Truck(int x, int y, int cell_size, std::vector<sf::RectangleShape> roads) {
		this->x_ = x;
		this->y_ = y;
		this->speed_ = 3;
		this->roads_ = roads;
		this->cellSize_ = cell_size;
        for (int i = 0; i < 3; i++) {
            this->seenByCamera_[i] = false;
        }
		this->sidewalkSize_ = round(SIDEWALK_SIZE * cellSize_ / ROAD_IMAGE_SIZE);
		this->roadSize_ = round(ROAD_SIZE * cellSize_ / ROAD_IMAGE_SIZE);
		this->roadStripesSize_ = round(ROAD_STRIPES_SIZE * cellSize_ / ROAD_IMAGE_SIZE);
		this->direction_ = "South";
		this->previousDirection_ = "";
		this->currentRoad_ = nullptr;
		this->previousRoad_ = nullptr;
		this->shape_.setFillColor(sf::Color(0, 0, 255));
        this->shape_.setSize(sf::Vector2f(round(14 * cell_size/ROAD_IMAGE_SIZE), round(20 * cell_size / ROAD_IMAGE_SIZE)));
		this->shape_.setOrigin(this->shape_.getSize().x / 2, this->shape_.getSize().y / 2);
		this->shape_.setPosition(sf::Vector2f(x, y));
		this->colisionBox_.setFillColor(sf::Color::Yellow);
		this->colisionBox_.setSize(sf::Vector2f(round(14 * cell_size / ROAD_IMAGE_SIZE), round(14 * cell_size / ROAD_IMAGE_SIZE)));
		this->colisionBox_.setOrigin(this->colisionBox_.getSize().x / 2, this->colisionBox_.getSize().y / 2);
		this->colisionBox_.setPosition(sf::Vector2f(this->shape_.getPosition().x, this->shape_.getPosition().y + (this->colisionBox_.getSize().y / 2 + this->shape_.getSize().y / 2 + this->roadStripesSize_)));
	}
}
