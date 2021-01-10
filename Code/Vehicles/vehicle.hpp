#pragma once
#include "SFML/Graphics.hpp"
#include "../definitions.hpp"
#include "../cell.hpp"
#include <chrono>
namespace zpr {
	class Vehicle : public sf::Drawable
	{
	public:
		virtual ~Vehicle() {};
		sf::RectangleShape getShape();
		void move();
		void checkOnWhichCell(int drawPrefix);
		void checkTurn();
		void stopVehicle();
		void noColision();
		bool checkColision(std::shared_ptr<Vehicle> vehicle);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		int x_, y_, speed_;
		int roadSize_, sidewalkSize_, roadStripesSize_;
		int cellSize_;
		bool seenByCamera_[3];
		std::vector<sf::RectangleShape> roads_;
		std::string direction_, previousDirection_;
		sf::RectangleShape shape_, colisionBox_;
		std::shared_ptr<sf::RectangleShape> currentRoad_, previousRoad_;

	private:
		void updatePosition();
		void updateColisionBoxPosition();
		void checkIfSeenByCamera();
		void turnBack();
		void choseFromOneRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void choseFromTwoRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void choseFromThreeRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void updateDirection(std::string direction);
	};
}

