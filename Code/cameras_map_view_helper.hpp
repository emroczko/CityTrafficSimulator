/**
 * cameras_map_view_helper.hpp
 * Header of CamerasHelper class.
 */


#pragma once

#include "SFML/Graphics.hpp"
#include "simulator.hpp"
#include "converter.hpp"


namespace zpr {

    /**
     * Class responsible for helping handling cameras in map view.
     */
    class CamerasHelper{
    public:
        CamerasHelper(int cell_size);
        bool checkCameraExists(sf::Vector2f position, sf::RectangleShape *cameras);
    private:
        int cellSize_;
    };
}
