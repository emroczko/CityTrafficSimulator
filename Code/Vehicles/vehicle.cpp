/**
 * vehicle.cpp
 * Implementation of Vehicle class.
 */

#include "vehicle.hpp"
#include <random>

namespace zpr {

    /**
     * Method returning shape of the Vehicle.
     * @return - Shape of the vehicle.
     */
    sf::RectangleShape Vehicle::getShape()
    {
        return this->shape_;
    }

    /**
     * Method responsible for moving the vehices.
     */
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

    /**
     * Method responsible for updating Vehicle's position.
     */
    void Vehicle::updatePosition() {
        this->shape_.setPosition(sf::Vector2f(x_, y_));
    }

    /**
     * Method responsible for updating Vehicle's collision box position.
     */
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

	bool Vehicle::canTurnBack()
	{
		for (sf::RectangleShape road : this->roads_) {
			if (this->direction_ == "South" && road.getPosition().x == this->currentRoad_->getPosition().x && road.getPosition().y == this->currentRoad_->getPosition().y-this->cellSize_) {
				return true;
			}
			if (this->direction_ == "North" && road.getPosition().x == this->currentRoad_->getPosition().x && road.getPosition().y == this->currentRoad_->getPosition().y + this->cellSize_) {
				return true;
			}
			if (this->direction_ == "East" && road.getPosition().x == this->currentRoad_->getPosition().x - this->cellSize_ && road.getPosition().y == this->currentRoad_->getPosition().y) {
				return true;
			}
			if (this->direction_ == "West" && road.getPosition().x == this->currentRoad_->getPosition().x + this->cellSize_ && road.getPosition().y == this->currentRoad_->getPosition().y) {
				return true;
			}
		}
		return false;
	}

    /**
     * Method responsible for checking on which cell Vehicle is.
     */
    void Vehicle::checkOnWhichCell()
    {
        std::shared_ptr<sf::RectangleShape> temp_cell = nullptr;
        if (this->roads_.size() != 0) {
            if (!previousRoad_ || this->currentRoad_->getPosition() == this->previousRoad_->getPosition()) {
                for (sf::RectangleShape road : this->roads_) {
                    if (road.getGlobalBounds().contains(this->shape_.getPosition())) {
                        temp_cell = std::make_shared<sf::RectangleShape>(road);
                        this->previousRoad_ = this->currentRoad_;
                        this->currentRoad_ = temp_cell;
                    }
                }
            }
        }
    }
    
    /**
     * Method reponsible for checking if there is a vehicle in front of other vehicle and if there is method stops the vehicle.
     * @param vehicle - Vehicle we are checking.
     * @return - True if there is a collision, false otherwise.
     */
    bool Vehicle::checkColision(std::shared_ptr<Vehicle> vehicle){
        bool colision = this->colisionBox_.getGlobalBounds().intersects(vehicle->getShape().getGlobalBounds());
        if (colision){
            return true;
        }
        return false;
    }

    /**
     * Method responsible for checking if vehicle can turn or not.
     */
    void Vehicle::checkTurn()
    {
        if (previousRoad_) {
            if (this->currentRoad_->getPosition() != this->previousRoad_->getPosition())
            {
                std::shared_ptr<sf::RectangleShape> north = nullptr;
                std::shared_ptr<sf::RectangleShape> south = nullptr;
                std::shared_ptr<sf::RectangleShape> east = nullptr;
                std::shared_ptr<sf::RectangleShape> west = nullptr;
                std::vector<std::shared_ptr<sf::RectangleShape>> neighbouring_roads;
                for (sf::RectangleShape road : this->roads_) {
                    if (road.getGlobalBounds() != this->previousRoad_->getGlobalBounds()) {
                        if (road.getPosition().y == this->currentRoad_->getPosition().y) {
                            if (road.getPosition().x == this->currentRoad_->getPosition().x + this->cellSize_) {
                                east = std::make_shared<sf::RectangleShape>(road);
                                neighbouring_roads.push_back(east);
                            }
                            else if (road.getPosition().x == this->currentRoad_->getPosition().x - this->cellSize_) {
                                west = std::make_shared<sf::RectangleShape>(road);
                                neighbouring_roads.push_back(west);
                            }
                        }
                        else if (road.getPosition().x == this->currentRoad_->getPosition().x) {
                            if (road.getPosition().y == this->currentRoad_->getPosition().y + this->cellSize_) {
                                south = std::make_shared<sf::RectangleShape>(road);
                                neighbouring_roads.push_back(south);
                            }
                            else if (road.getPosition().y == this->currentRoad_->getPosition().y - this->cellSize_) {
                                north = std::make_shared<sf::RectangleShape>(road);
                                neighbouring_roads.push_back(north);
                            }
                        }
                    }
                }
                switch (neighbouring_roads.size()) {
                case 0: this->turnBack(); break;
                case 1: this->choseFromOneRoads(north, south, east, west); break;
                case 2: this->choseFromTwoRoads(north, south, east, west); break;
                case 3: this->choseFromThreeRoads(north, south, east, west); break;
                }
                this->previousRoad_ = this->currentRoad_;
            }
        }
    }
    
    /**
     * Method responsible for stopping the vehicle.
     */
    void Vehicle::stopVehicle()
    {
        this->speed_ = 0;
    }

	void Vehicle::checkVehicleStopped()
	{
		if (this->speed_ == 0) {
			this->stopCounter_++;
		}
		else {
			this->stopCounter_ = 0;
		}
	}

	void Vehicle::unblockVehicle()
	{
		if (this->stopCounter_ > 100 && this->canTurnBack()) {
			this->turnBack();
			this->stopCounter_ = 0;
		}
	}

    /**
     * Method responsible for setting the speed of vehicle if there is no colision.
     */
    void Vehicle::noColision()
    {
        this->speed_ = 3;
    }

    /**
     * Method responsible for turning the vehicle back.
     */
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
    
    /**
     * Method responsible for choosing the road from one road when the car is about to turn.
     * @param north - RectangleShape object representing road above.
     * @param south - RectangleShape object representing road under.
     * @param east - RectangleShape object representing road on the right.
     * @param west - RectangleShape object representing road on the left.
     */
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

    /**
     * Method responsible for choosing the road from two roads when the car is about to turn.
     * @param north - RectangleShape object representing road above.
     * @param south - RectangleShape object representing road under.
     * @param east - RectangleShape object representing road on the right.
     * @param west - RectangleShape object representing road on the left.
     */
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

    /**
     * Method responsible for choosing the road from three roads when the car is about to turn.
     * @param north - RectangleShape object representing road above.
     * @param south - RectangleShape object representing road under.
     * @param east - RectangleShape object representing road on the right.
     * @param west - RectangleShape object representing road on the left.
     */
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

    /**
     * Method responsible for updating the direction of the vehicle.
     * @param direction - Direction of the vehicle.
     */
    void Vehicle::updateDirection(std::string direction)
    {
        this->direction_ = direction;
    }

    /**
     * Method responsible for drawing the vehicle.
     * @param target - Object where to draw the vehicle.
     * @param states - sf::RenderStates object.
     */
    void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(this->shape_, states);
    }
}
