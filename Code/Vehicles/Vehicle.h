#pragma once
#include "SFML/Graphics.hpp"
#include "../Definitions.h"
#include "../Cell.h"
#include <chrono>
namespace ZPR {
	class Vehicle : public sf::Drawable
	{
	public:
		virtual ~Vehicle() {};
		sf::RectangleShape getShape();
		void move();
		void CheckOnWhichCell(int drawPrefix);
		void CheckTurn();
		void StopVehicle();
		void NoColision();
		bool CheckColision(std::shared_ptr<Vehicle> vehicle);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		int _x, _y, _speed;
		int _roadSize, _sidewalkSize, _roadStripesSize;
		int _cellSize;
		bool _seenByCamera;
		std::vector<sf::RectangleShape> _roads;
		std::string _direction, _previousDirection;
		sf::RectangleShape _shape, _colisionBox;
		std::shared_ptr<sf::RectangleShape> _currentRoad, _previousRoad;
	private:
		void UpdatePosition();
		void UpdateColisionBoxPosition();
		void CheckIfSeenByCamera();
		void TurnBack();
		void ChoseFromOneRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void ChoseFromTwoRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void ChoseFromThreeRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void UpdateDirection(std::string direction);
	};
}

