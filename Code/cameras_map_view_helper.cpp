/**
 * cameras_map_view_helper.hpp
 * Implementation of CamerasHelper class.
 */

#include "cameras_map_view_helper.hpp"


namespace zpr {

    /**
     * Parametrized constructor of CamerasHelper class.
     * @param cell_size - Size of a cell in map view.
     */
    CamerasHelper::CamerasHelper(int cell_size): cellSize_(cell_size){}

    /**
     * Method responsible for checking if camera exists on given position.
     * @param position - Position where road can exist.
     * @param cameras - Table of cameras existing in map view.
     * @return - True when camera exists, false otherwise.
     */
    bool CamerasHelper::checkCameraExists(sf::Vector2f position, sf::RectangleShape *cameras) {
       
        for(int i = 0; i < 3; i++){
            if (cameras[i].getPosition().x -this->cellSize_/2 == position.x && cameras[i].getPosition().y - this->cellSize_/2 == position.y) {
                return true;
            }
        }
        return false;
    }
}
