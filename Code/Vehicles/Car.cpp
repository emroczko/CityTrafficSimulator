#include "Car.h"
#include <iostream>

Car::Car(int x, int y) {
	this->x = x;
	this->y = y;
	speed = 1;
	shape.setFillColor(sf::Color(255, 255, 255));
	shape.setSize(sf::Vector2f(100, 100));
	shape.setPosition(sf::Vector2f(x, y));
}

Car::~Car() {

}

void Car::move() {
	srand((unsigned)time(NULL));
	switch (rand()%4)
	{
		case 0: x += speed; break;
		case 1: x -= speed; break;
		case 2: y += speed; break;
		case 3: y -= speed; break;
	}
	if (x>1200)
	{
		x = 1100;
	}
	if (y>800)
	{
		y = 700;
	}
	if (x<0)
	{
		x < 0;
	}
	if (y<0)
	{
		y = 0;
	}
	updatePosition();
}

void Car::updatePosition() {
	shape.setPosition(sf::Vector2f(x, y));
}

sf::RectangleShape Car::getShape() {
	return shape;
}
