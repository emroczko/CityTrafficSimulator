#include "InputManager.h"

namespace ZPR{

/**
 Metoda sprawdzająca czy  za pomocą myszki został kliknięty obiekt
 */
    bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window){
        if (sf::Mouse::isButtonPressed(button)){
            sf::IntRect tempRect(object.getPosition().x, object.getPosition().y,
                                 object.getGlobalBounds().width, object.getGlobalBounds().height );
            if (tempRect.contains(sf::Mouse::getPosition(window))){
                return true;
            }
        }
        return false;
    }
/**
 Metoda pobierająca położenie myszki
 */
    sf::Vector2i GetMousePosition(sf::RenderWindow &window){
        return sf::Mouse::getPosition(window);
    }

}
