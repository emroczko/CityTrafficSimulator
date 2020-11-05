#include <SFML/Graphics.hpp>
#include "Vehicles/Car.h"
#include "Menu.h"
#include <iostream>

using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode(2160, 1680), "SFML WORK!");

        Menu menu(window.getSize().x, window.getSize().y);

        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;

                    case sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            std::cout << "Play button has been pressed" << std::endl;
                            break;
                        case 1:
                            std::cout << "Option button has been pressed" << std::endl;
                            break;
                        case 2:
                            window.close();
                            break;
                        }

                        break;
                    }

                    break;
                case sf::Event::Closed:
                    window.close();

                    break;

                }
            }

            window.clear();

            menu.draw(window);

            window.display();
        }
	return 0;
}



/*
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
    }*/
