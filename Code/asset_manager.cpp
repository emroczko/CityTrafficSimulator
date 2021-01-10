/**
 * asset_manager.cpp
 * Implementation of AssetManager class.
 */

#include "asset_manager.hpp"

namespace zpr {

    /**
     * Method which loads texture from file into sf::Texture map.
     * @param name - Name of texture.
     * @param file_name - Name of file from which texture is loaded.
     */
    void AssetManager::loadTexture(std::string name, std::string file_name){
        sf::Texture texture;
    
        if (texture.loadFromFile(file_name))
            this-> textures_[name] = texture;
    }

    /**
     * Method which returns sf::Texture.
     * @param name - Name of texture.
     * @return - sf::Texture object we want to use.
     */
    sf::Texture &AssetManager::getTexture(std::string name){
        return this-> textures_.at(name);
    }
    
    /**
     * Method which loads font from file into sf::Font map.
     * @param name - Name of font.
     * @param file_name - Name od file from which font is loaded.
     */
    void AssetManager::loadFont(std::string name, std::string file_name){
        sf::Font font;
    
        if (font.loadFromFile(file_name))
            this-> fonts_[name] = font;
    }

    /**
     * Method which returns sf::Font.
     * @param name - Name of font.
     * @return - sf::Font object we want to use. 
     */
    sf::Font &AssetManager::getFont(std::string name){
        return this-> fonts_.at(name);
    }

}
