/**
 * input_manager.hpp
 * Header for InputManager class.
 */
#pragma once

#include <SFML/Graphics.hpp>

namespace zpr{

    /**
     Class responsible for handling user clicks. 
     */
    class InputManager {
    public:
        InputManager() { }
        ~InputManager() { }
    
        bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
        bool isSquareClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow& window);
        sf::Vector2i getMousePosition(sf::RenderWindow &window);
    
    };

}
