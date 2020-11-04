//
//  main.cpp
//  CityTrafficSimulator
//
//  Created by Eryk Mroczko on 04/11/2020.
//

#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, const char * argv[]) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Blue);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

        return 0;
}
