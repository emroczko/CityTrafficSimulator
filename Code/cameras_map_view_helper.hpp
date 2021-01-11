//
//  cameras_map_view_helper.hpp
//  CityTrafficSimulator
//
//  Created by Eryk Mroczko on 11/01/2021.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "simulator.hpp"
#include "converter.hpp"


namespace zpr {

    class CamerasHelper{
    public:
        CamerasHelper(int cell_size);
        bool checkCameraExists(sf::Vector2f position, sf::RectangleShape *cameras);
    private:
        int cellSize_;
    };
}
