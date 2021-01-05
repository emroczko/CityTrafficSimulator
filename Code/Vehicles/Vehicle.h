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
		virtual sf::RectangleShape getShape();
		void move();
		void UpdatePosition();
		void CheckOnWhichCell(int drawPrefix);
		void CheckTurn();
		void TurnBack();
		void ChoseFromOneRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void ChoseFromTwoRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void ChoseFromThreeRoads(std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void UpdateDirection(std::string direction);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		int _x, _y, _speed;
		int _roadSize, _sidewalkSize, _roadStripesSize;
		std::shared_ptr<sf::RectangleShape> _currentRoad, _previousRoad;
		int _cellSize;
		std::vector<sf::RectangleShape> _roads;
		std::string _direction;
		sf::RectangleShape _shape;
	};
}

