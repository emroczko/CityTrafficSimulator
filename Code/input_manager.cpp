/**
 * input_manager.cpp
 * Implementation of InputManager class.
 */

#include "input_manager.hpp"

namespace zpr{

    /**
     * Methods responsible for checking if Sprite object was clicked.
     * @param object - Sprite object which was/wasn't clicked.
     * @param button - Mouse button.
     * @param window - Application window.
     * @return - True when sprite is clicked or false when not.
     */
    bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window){
        if (sf::Mouse::isButtonPressed(button)){
            sf::IntRect temp_rect(object.getPosition().x, object.getPosition().y,
                                 object.getGlobalBounds().width, object.getGlobalBounds().height );
            if (temp_rect.contains(sf::Mouse::getPosition(window))){
                return true;
            }
        }
        return false;
    }
    /**
     * Method responsible for getting mouse position.
     * @param window - Application window.
     * @return - Position of mouse.
     */
    sf::Vector2i GetMousePosition(sf::RenderWindow &window){
        return sf::Mouse::getPosition(window);
    }

}
