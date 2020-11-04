#include <SFML/Graphics.hpp>
#include "Vehicles/Car.h"
#include <iostream>

using namespace std;
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(1200, 800), "City Traffic Simulator", sf::Style::Close | sf::Style::Titlebar);
	vector<Car> cars;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10; i++) {
		cars.push_back(Car(rand()%500 + 300, rand() % 500 + 300));
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (int i = 0; i < 10; i++) {
			window.draw(cars.at(i).getShape());
			cars.at(i).move();
		}
		window.clear();
		window.display();
	}

	return 0;
}