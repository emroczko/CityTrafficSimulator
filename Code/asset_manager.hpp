/**
 * asset_manager.hpp
 * Header of AssetManager class.
 */

#pragma once

#include <map>
#include <SFML/Graphics.hpp>

namespace zpr{

    /**
     * Class responsible for loading textures and fonts from files. 
     */
    class AssetManager{
    public:
        AssetManager() {}
        ~AssetManager() {}
    
        void loadTexture(std::string name, std::string file_name);
        sf::Texture &getTexture(std::string name);
        void loadFont(std::string name, std::string file_name);
        sf::Font &getFont(std::string name);
    private:
        std::map<std::string, sf::Texture> textures_;
        std::map<std::string, sf::Font> fonts_;

    };

}
