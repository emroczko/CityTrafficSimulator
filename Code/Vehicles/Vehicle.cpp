#include "Vehicle.h"
#include <random>
namespace ZPR {
	sf::RectangleShape Vehicle::getShape()
	{
		return this->_shape;
	}
	void Vehicle::move()
	{
		if (_direction == "North") {
			this->_shape.setRotation(0);
			this->_x = this->_currentRoad->getPosition().x + this->_roadSize / 2 + this->_roadStripesSize;
			this->_y -= this->_speed;
		}
		else if (_direction == "South") {
			this->_shape.setRotation(0);
			this->_x = this->_currentRoad->getPosition().x - this->_roadSize / 2 - this->_roadStripesSize;
			this->_y += this->_speed;
		}
		else if (_direction == "East") {
			this->_shape.setRotation(90);
			this->_y = this->_currentRoad->getPosition().y + this->_roadSize / 2 + this->_roadStripesSize;
			this->_x += this->_speed;
		}
		else if (_direction == "West") {
			this->_shape.setRotation(90);
			this->_y = this->_currentRoad->getPosition().y - this->_roadSize / 2 - this->_roadStripesSize;
			this->_x -= this->_speed;
		}
		else if (_direction == "Stop") {

		}
		UpdatePosition();
		UpdateColisionBoxPosition();
	}
	void Vehicle::UpdatePosition() {
		this->_shape.setPosition(sf::Vector2f(_x, _y));
	}
	void Vehicle::UpdateColisionBoxPosition() {
		if (this->_direction == "South") {
			this->_colisionBox.setPosition(sf::Vector2f(this->_shape.getPosition().x, this->_shape.getPosition().y + (this->_colisionBox.getSize().y / 2 + this->_shape.getSize().y / 2 + this->_roadStripesSize)));
		}
		else if (this->_direction == "North") {
			this->_colisionBox.setPosition(sf::Vector2f(this->_shape.getPosition().x, this->_shape.getPosition().y - (this->_colisionBox.getSize().y / 2 + this->_shape.getSize().y / 2 + this->_roadStripesSize)));
		}
		else if (this->_direction == "East"){
			this->_colisionBox.setPosition(sf::Vector2f(this->_shape.getPosition().x + (this->_colisionBox.getSize().x / 2 + this->_shape.getSize().x / 2 + this->_roadStripesSize), this->_shape.getPosition().y));
		}
		else {
			this->_colisionBox.setPosition(sf::Vector2f(this->_shape.getPosition().x - (this->_colisionBox.getSize().x / 2 + this->_shape.getSize().y / 2 + this->_roadStripesSize), this->_shape.getPosition().y));
		}
	}

	void Vehicle::CheckOnWhichCell(int drawPrefix)
	{
		std::shared_ptr<sf::RectangleShape> tempCell = nullptr;
		if (this->_roads.size() != 0) {
			if (!_previousRoad || this->_currentRoad->getPosition() == this->_previousRoad->getPosition()) {
				for (sf::RectangleShape road : this->_roads) {
					if (road.getGlobalBounds().contains(this->_shape.getPosition())) {
						tempCell = std::make_shared<sf::RectangleShape>(road);
						this->_previousRoad = this->_currentRoad;
						this->_currentRoad = tempCell;
					}
				}
			}
		}
	}
	//Sprawdza czy przed pojadem znajduje siê inny pojazd i je¿eli tak sie stanie to zatrzymuje go w miejscu					//
	void Vehicle::CheckColision(std::shared_ptr<Vehicle> vehicle){
		bool colision = this->_colisionBox.getGlobalBounds().intersects(vehicle->getShape().getGlobalBounds());
		if (colision){
			this->_speed = 0;
		}
		//else {
			//this->_speed = 3;
		//}
		
	}

	void Vehicle::CheckTurn()
	{
		if (_previousRoad) {
			if (this->_currentRoad->getPosition() != this->_previousRoad->getPosition())
			{
				std::shared_ptr<sf::RectangleShape> north = nullptr;
				std::shared_ptr<sf::RectangleShape> south = nullptr;
				std::shared_ptr<sf::RectangleShape> east = nullptr;
				std::shared_ptr<sf::RectangleShape> west = nullptr;
				std::vector<std::shared_ptr<sf::RectangleShape>> neighbouringRoads;
				for (sf::RectangleShape road : this->_roads) {
					if (road.getGlobalBounds() != this->_previousRoad->getGlobalBounds()) {
						if (road.getPosition().y == this->_currentRoad->getPosition().y) {
							if (road.getPosition().x == this->_currentRoad->getPosition().x + this->_cellSize) {
								east = std::make_shared<sf::RectangleShape>(road);
								neighbouringRoads.push_back(east);
							}
							else if (road.getPosition().x == this->_currentRoad->getPosition().x - this->_cellSize) {
								west = std::make_shared<sf::RectangleShape>(road);
								neighbouringRoads.push_back(west);
							}
						}
						else if (road.getPosition().x == this->_currentRoad->getPosition().x) {
							if (road.getPosition().y == this->_currentRoad->getPosition().y + this->_cellSize) {
								south = std::make_shared<sf::RectangleShape>(road);
								neighbouringRoads.push_back(south);
							}
							else if (road.getPosition().y == this->_currentRoad->getPosition().y - this->_cellSize) {
								north = std::make_shared<sf::RectangleShape>(road);
								neighbouringRoads.push_back(north);
							}
						}
					}
				}
				switch (neighbouringRoads.size()) {
				case 0: TurnBack(); break;
				case 1: ChoseFromOneRoads(north, south, east, west); break;
				case 2: ChoseFromTwoRoads(north, south, east, west); break;
				case 3: ChoseFromThreeRoads(north, south, east, west); break;
				}
				this->_previousRoad = this->_currentRoad;
			}
		}
	}
	void Vehicle::TurnBack() {
		if (this->_direction == "North") {
			this->_direction = "South";
		}
		else if (this->_direction == "South") {
			this->_direction = "North";
		}
		else if (this->_direction == "East") {
			this->_direction = "West";
		}
		else if (this->_direction == "West") {
			this->_direction = "East";
		}
	}
	void Vehicle::ChoseFromOneRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
	{

		if (north) {
			this->UpdateDirection("North");
		}
		else if (south) {
			this->UpdateDirection("South");
		}
		else if (east) {
			this->UpdateDirection("East");
		}
		else if (west) {
			this->UpdateDirection("West");
		}
	}

	void Vehicle::ChoseFromTwoRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
	{
		std::random_device rng;
		std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> dist(1, 2);
		int num = dist(eng);
		if (north && south) {
			switch (num)
			{
			case 1: this->UpdateDirection("North"); break;
			case 2: this->UpdateDirection("South"); break;
			}
		}
		else if (north && east) {
			switch (num)
			{
			case 1: this->UpdateDirection("North"); break;
			case 2: this->UpdateDirection("East"); break;
			}
		}
		else if (north && west) {
			switch (num)
			{
			case 1: this->UpdateDirection("North"); break;
			case 2: this->UpdateDirection("West"); break;
			}
		}
		else if (south && east) {
			switch (num)
			{
			case 1: this->UpdateDirection("South"); break;
			case 2: this->UpdateDirection("East"); break;
			}
		}
		else if (south && west) {
			switch (num)
			{
			case 1: this->UpdateDirection("South"); break;
			case 2: this->UpdateDirection("West"); break;
			}
		}
		else if (east && west) {
			switch (num)
			{
			case 1: this->UpdateDirection("East"); break;
			case 2: this->UpdateDirection("West"); break;
			}
		}
	}

	void Vehicle::ChoseFromThreeRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
	{
		std::random_device rng;
		std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> dist(1, 3);
		int num = dist(eng);
		if (north && south && east) {
			switch (num) {
			case 1: this->UpdateDirection("North"); break;
			case 2: this->UpdateDirection("South"); break;
			case 3: this->UpdateDirection("East"); break;
			}
		}
		else if (north && south && west) {
			switch (num) {
			case 1: this->UpdateDirection("North"); break;
			case 2: this->UpdateDirection("South"); break;
			case 3: this->UpdateDirection("West"); break;
			}
		}
		else if (north && east && west) {
			switch (num) {
			case 1: this->UpdateDirection("North"); break;
			case 2: this->UpdateDirection("East"); break;
			case 3: this->UpdateDirection("West"); break;
			}
		}
		else if (south && east && west) {
			switch (num) {
			case 1: this->UpdateDirection("South"); break;
			case 2: this->UpdateDirection("East"); break;
			case 3: this->UpdateDirection("West"); break;
			}
		}
	}

	void Vehicle::UpdateDirection(std::string direction)
	{
		this->_direction = direction;
	}
	void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->_shape, states);
		target.draw(this->_colisionBox, states);
	}
}
