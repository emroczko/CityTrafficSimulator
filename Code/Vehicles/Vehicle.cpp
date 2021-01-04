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
		UpdatePosition();
	}
	void Vehicle::UpdatePosition() {
		this->_shape.setPosition(sf::Vector2f(_x, _y));
	}
	void Vehicle::CheckOnWhichCell(int drawPrefix)
	{
		std::shared_ptr<Cell> tempCell = nullptr;
		if (this->_roads.size() != 0) {
			for (Cell road : this->_roads) {
				//if (this->_shape.getRotation() == 0) {
				if ((this->_x > drawPrefix + road.GetPosition().y * this->_cellSize) && (this->_x < drawPrefix + (road.GetPosition().y + 1) * this->_cellSize)) {
					if ((this->_y > drawPrefix + road.GetPosition().x * this->_cellSize) && (this->_y < drawPrefix + ((road.GetPosition().x + 1) * this->_cellSize))) {
						tempCell = std::make_shared<Cell>(road);
						this->_previousCell = this->_currentCell;
						this->_currentCell = tempCell;
					}
				}
				//}
			}
		}

	}
	void Vehicle::CheckTurn()
	{
		if (this->_currentCell->GetPosition() != this->_previousCell->GetPosition())
		{
			std::shared_ptr<Cell> north = nullptr;
			std::shared_ptr<Cell> south = nullptr;
			std::shared_ptr<Cell> east = nullptr;
			std::shared_ptr<Cell> west = nullptr;
			std::vector<std::shared_ptr<Cell>> neighbouringRoads;
			for (Cell road : this->_roads) {
				if (road.GetPosition().x != this->_previousCell->GetPosition().x && road.GetPosition().y != this->_previousCell->GetPosition().y) {
					if (road.GetPosition().y == this->_currentCell->GetPosition().y) {
						if (road.GetPosition().x == this->_currentCell->GetPosition().x + 1) {
							east = std::make_shared<Cell>(road);
							neighbouringRoads.push_back(east);
						}
						else if (road.GetPosition().x == this->_currentCell->GetPosition().x - 1) {
							west = std::make_shared<Cell>(road);
							neighbouringRoads.push_back(west);
						}
					}
					else if (road.GetPosition().x == this->_currentCell->GetPosition().x) {
						if (road.GetPosition().y == this->_currentCell->GetPosition().y + 1) {
							south = std::make_shared<Cell>(road);
							neighbouringRoads.push_back(south);
						}
						else if (road.GetPosition().x == this->_currentCell->GetPosition().x - 1) {
							north = std::make_shared<Cell>(road);
							neighbouringRoads.push_back(north);
						}
					}
				}
			}
			switch (neighbouringRoads.size()) {
			case 1: ChoseFromOneRoads(north, south, east, west); break;
			case 2: ChoseFromTwoRoads(north, south, east, west); break;
			case 3: ChoseFromThreeRoads(north, south, east, west); break;
			}
			this->_previousCell = this->_currentCell;
		}
	}

	void Vehicle::ChoseFromOneRoads(std::shared_ptr<Cell> north, std::shared_ptr<Cell> south, std::shared_ptr<Cell> east, std::shared_ptr<Cell> west)
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

	void Vehicle::ChoseFromTwoRoads(std::shared_ptr<Cell> north, std::shared_ptr<Cell> south, std::shared_ptr<Cell> east, std::shared_ptr<Cell> west)
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

	void Vehicle::ChoseFromThreeRoads(std::shared_ptr<Cell> north, std::shared_ptr<Cell> south, std::shared_ptr<Cell> east, std::shared_ptr<Cell> west)
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
	}
}
