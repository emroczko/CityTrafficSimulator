#include "vehicle.hpp"
#include <random>
namespace zpr {
	sf::RectangleShape Vehicle::getShape()
	{
		return this->shape_;
	}
	void Vehicle::move()
	{
		if (direction_ == "North") {
			this->shape_.setRotation(0);
			this->x_ = this->currentRoad_->getPosition().x + this->roadSize_ / 2 + this->roadStripesSize_;
			this->y_ -= this->speed_;
		}
		else if (direction_ == "South") {
			this->shape_.setRotation(0);
			this->x_ = this->currentRoad_->getPosition().x - this->roadSize_ / 2 - this->roadStripesSize_;
			this->y_ += this->speed_;
		}
		else if (direction_ == "East") {
			this->shape_.setRotation(90);
			this->y_ = this->currentRoad_->getPosition().y + this->roadSize_ / 2 + this->roadStripesSize_;
			this->x_ += this->speed_;
		}
		else if (direction_ == "West") {
			this->shape_.setRotation(90);
			this->y_ = this->currentRoad_->getPosition().y - this->roadSize_ / 2 - this->roadStripesSize_;
			this->x_ -= this->speed_;
		}
		else if (direction_ == "Stop") {

		}
		this->updatePosition();
		this->updateColisionBoxPosition();
	}
	void Vehicle::updatePosition() {
		this->shape_.setPosition(sf::Vector2f(x_, y_));
	}
	void Vehicle::updateColisionBoxPosition() {
		if (this->direction_ == "South") {
			this->colisionBox_.setPosition(sf::Vector2f(this->shape_.getPosition().x, this->shape_.getPosition().y + (this->colisionBox_.getSize().y / 2 + this->shape_.getSize().y / 2 + this->roadStripesSize_)));
		}
		else if (this->direction_ == "North") {
			this->colisionBox_.setPosition(sf::Vector2f(this->shape_.getPosition().x, this->shape_.getPosition().y - (this->colisionBox_.getSize().y / 2 + this->shape_.getSize().y / 2 + this->roadStripesSize_)));
		}
		else if (this->direction_ == "East"){
			this->colisionBox_.setPosition(sf::Vector2f(this->shape_.getPosition().x + (this->colisionBox_.getSize().x / 2 + ceil(this->shape_.getSize().x / 2) + this->roadStripesSize_), this->shape_.getPosition().y));
		}
		else {
			this->colisionBox_.setPosition(sf::Vector2f(this->shape_.getPosition().x - (this->colisionBox_.getSize().x / 2 + ceil(this->shape_.getSize().y / 2) + this->roadStripesSize_), this->shape_.getPosition().y));
		}
	}

	void Vehicle::checkOnWhichCell(int drawPrefix)
	{
		std::shared_ptr<sf::RectangleShape> tempCell = nullptr;
		if (this->roads_.size() != 0) {
			if (!previousRoad_ || this->currentRoad_->getPosition() == this->previousRoad_->getPosition()) {
				for (sf::RectangleShape road : this->roads_) {
					if (road.getGlobalBounds().contains(this->shape_.getPosition())) {
						tempCell = std::make_shared<sf::RectangleShape>(road);
						this->previousRoad_ = this->currentRoad_;
						this->currentRoad_ = tempCell;
					}
				}
			}
		}
		this->checkIfSeenByCamera();
	}
	//Sprawdza czy przed pojadem znajduje siê inny pojazd i je¿eli tak sie stanie to zatrzymuje go w miejscu					//
	bool Vehicle::checkColision(std::shared_ptr<Vehicle> vehicle){
		bool colision = this->colisionBox_.getGlobalBounds().intersects(vehicle->getShape().getGlobalBounds());
		if (colision){
			return true;
		}
		return false;
	}

	void Vehicle::checkIfSeenByCamera()
	{
		if (this->currentRoad_ == this->previousRoad_) {
			this->seenByCamera_ = true;
		}
		else {
			this->seenByCamera_ = false;
		}
	}

	void Vehicle::checkTurn()
	{
		if (previousRoad_) {
			if (this->currentRoad_->getPosition() != this->previousRoad_->getPosition())
			{
				std::shared_ptr<sf::RectangleShape> north = nullptr;
				std::shared_ptr<sf::RectangleShape> south = nullptr;
				std::shared_ptr<sf::RectangleShape> east = nullptr;
				std::shared_ptr<sf::RectangleShape> west = nullptr;
				std::vector<std::shared_ptr<sf::RectangleShape>> neighbouringRoads;
				for (sf::RectangleShape road : this->roads_) {
					if (road.getGlobalBounds() != this->previousRoad_->getGlobalBounds()) {
						if (road.getPosition().y == this->currentRoad_->getPosition().y) {
							if (road.getPosition().x == this->currentRoad_->getPosition().x + this->cellSize_) {
								east = std::make_shared<sf::RectangleShape>(road);
								neighbouringRoads.push_back(east);
							}
							else if (road.getPosition().x == this->currentRoad_->getPosition().x - this->cellSize_) {
								west = std::make_shared<sf::RectangleShape>(road);
								neighbouringRoads.push_back(west);
							}
						}
						else if (road.getPosition().x == this->currentRoad_->getPosition().x) {
							if (road.getPosition().y == this->currentRoad_->getPosition().y + this->cellSize_) {
								south = std::make_shared<sf::RectangleShape>(road);
								neighbouringRoads.push_back(south);
							}
							else if (road.getPosition().y == this->currentRoad_->getPosition().y - this->cellSize_) {
								north = std::make_shared<sf::RectangleShape>(road);
								neighbouringRoads.push_back(north);
							}
						}
					}
				}
				switch (neighbouringRoads.size()) {
				case 0: this->turnBack(); break;
				case 1: this->choseFromOneRoads(north, south, east, west); break;
				case 2: this->choseFromTwoRoads(north, south, east, west); break;
				case 3: this->choseFromThreeRoads(north, south, east, west); break;
				}
				this->previousRoad_ = this->currentRoad_;
			}
		}
	}
	void Vehicle::stopVehicle()
	{
		this->speed_ = 0;
	}
	void Vehicle::noColision()
	{
		this->speed_ = 3;
	}
	void Vehicle::turnBack() {
		if (this->direction_ == "North") {
			this->direction_ = "South";
		}
		else if (this->direction_ == "South") {
			this->direction_ = "North";
		}
		else if (this->direction_ == "East") {
			this->direction_ = "West";
		}
		else if (this->direction_ == "West") {
			this->direction_ = "East";
		}
	}
	void Vehicle::choseFromOneRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
	{

		if (north) {
			this->updateDirection("North");
		}
		else if (south) {
			this->updateDirection("South");
		}
		else if (east) {
			this->updateDirection("East");
		}
		else if (west) {
			this->updateDirection("West");
		}
	}

	void Vehicle::choseFromTwoRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
	{
		std::random_device rng;
		std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> dist(1, 2);
		int num = dist(eng);
		if (north && south) {
			switch (num)
			{
			case 1: this->updateDirection("North"); break;
			case 2: this->updateDirection("South"); break;
			}
		}
		else if (north && east) {
			switch (num)
			{
			case 1: this->updateDirection("North"); break;
			case 2: this->updateDirection("East"); break;
			}
		}
		else if (north && west) {
			switch (num)
			{
			case 1: this->updateDirection("North"); break;
			case 2: this->updateDirection("West"); break;
			}
		}
		else if (south && east) {
			switch (num)
			{
			case 1: this->updateDirection("South"); break;
			case 2: this->updateDirection("East"); break;
            }
		}
		else if (south && west) {
			switch (num)
			{
			case 1: this->updateDirection("South"); break;
			case 2: this->updateDirection("West"); break;
			}
		}
		else if (east && west) {
			switch (num)
			{
			case 1: this->updateDirection("East"); break;
			case 2: this->updateDirection("West"); break;
			}
		}
	}

	void Vehicle::choseFromThreeRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
	{
		std::random_device rng;
		std::mt19937 eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> dist(1, 3);
		int num = dist(eng);
		if (north && south && east) {
			switch (num) {
			case 1: this->updateDirection("North"); break;
			case 2: this->updateDirection("South"); break;
			case 3: this->updateDirection("East"); break;
			}
		}
		else if (north && south && west) {
			switch (num) {
			case 1: this->updateDirection("North"); break;
			case 2: this->updateDirection("South"); break;
			case 3: this->updateDirection("West"); break;
			}
		}
		else if (north && east && west) {
			switch (num) {
			case 1: this->updateDirection("North"); break;
			case 2: this->updateDirection("East"); break;
			case 3: this->updateDirection("West"); break;
			}
		}
		else if (south && east && west) {
			switch (num) {
			case 1: this->updateDirection("South"); break;
			case 2: this->updateDirection("East"); break;
			case 3: this->updateDirection("West"); break;
			}
		}
	}

	void Vehicle::updateDirection(std::string direction)
	{
		this->direction_ = direction;
	}
	void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->shape_, states);
		target.draw(this->colisionBox_, states);
	}
}
