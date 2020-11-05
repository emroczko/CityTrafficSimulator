#include "Menu.h"


Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("/Users/erykmroczko/Documents/Studia/ZPR/CityTrafficSimulator_ZPR/Resources/BebasNeue-Regular.ttf"))
    {
        // handle error
    }

    for(int i = 0; i<=2; i++){
        menu[i].setFont(font);
        menu[i].setCharacterSize(80);
        menu[i].setColor(sf::Color::Red);
        menu[i].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * (i+1)));
        menu[0].setString("Play");
        menu[1].setString("Options");
        menu[2].setString("Exit");
    }
    
    selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}
