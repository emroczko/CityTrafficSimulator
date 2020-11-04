#include <SFML/Graphics.hpp>
#include "Vehicles/Car.h"
#include <iostream>

using namespace std;
int main()
{

	sf::RenderWindow window(sf::VideoMode(1200, 800), "City Traffic Simulator", sf::Style::Close | sf::Style::Titlebar);
	srand((unsigned)time(NULL));

	Car car(rand() % 500 + 200, rand() % 500 + 200);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	
		window.clear();
		window.draw(car.getShape());
		car.move();
		window.display();
	}
	return 0;
}
