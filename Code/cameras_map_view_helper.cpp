//
//  cameras_map_view_helper.cpp
//  CityTrafficSimulator
//
//  Created by Eryk Mroczko on 11/01/2021.
//

#include "cameras_map_view_helper.hpp"


namespace zpr {
    CamerasHelper::CamerasHelper(int cell_size): cellSize_(cell_size){}

    /**
     * Method responsible for checking if camera exists on given position.
     * @param position - Position where road can exist.
     * @return - True when camera exists, false otherwise.
     */
    bool CamerasHelper::checkCameraExists(sf::Vector2f position, sf::RectangleShape *cameras) {
       
        for(int i = 0; i < 2; i++){
            if (cameras[i].getPosition().x -this->cellSize_/2 == position.x && cameras[i].getPosition().y - this->cellSize_/2 == position.y) {
                return true;
            }
        }
        return false;
    }
}
