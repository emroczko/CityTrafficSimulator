#pragma once
#include "SFML/Graphics.hpp"
class Car
{
	private:
		int x, y;
		int speed;
		sf::RectangleShape shape;
		void updatePosition();

	public:
		Car(int x, int y);
		~Car();
		void move();
		sf::RectangleShape getShape();
};
