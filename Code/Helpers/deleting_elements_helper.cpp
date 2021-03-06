/**
 * deleting_elements_helper.cpp
 * Implementation of DeletingHelper class.
 */

#include "deleting_elements_helper.hpp"

namespace zpr {

    /**
     * Parametrized constructor of DeletingHelper class.
     * @param data - Struct containing data of current application. (eg. window, assets).
     * @param grid_size - Size of the grid in map view.
     */
    DeletingHelper::DeletingHelper(SimulatorDataRef data, int grid_size): data_(data), gridSize_(grid_size){
        this->roadBuilderHelper_ = std::make_unique<RoadBuilderHelper>(this->data_, this->gridSize_);
        this->converter_ = std::make_unique<Converter>(this->gridSize_);
        this->cellSize_ = (SCREEN_HEIGHT / this->gridSize_);
        this->camerasHelper_ = std::make_unique<CamerasHelper>(this->cellSize_);
    }

    /**
     * Method responsible for deleting roads from the map.
     * @param position - Position of the road in row and column.
     * @param roads - Vector of roads existing in the map view.
     */
    void DeletingHelper::deleteRoad(sf::Vector2i position, std::vector<sf::RectangleShape> &roads){

            int i = 0;
            sf::Vector2f position_in_pixels = this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y));

            if(this->roadBuilderHelper_->checkRoadExists(this->converter_->transformRowColToPixels(sf::Vector2i(position_in_pixels.x, position_in_pixels.y)), roads)) { return; }
            
            for (sf::RectangleShape road : roads) {
                if (road.getPosition().x - this->cellSize_ / 2 == position_in_pixels.x && road.getPosition().y - this->cellSize_ / 2 == position_in_pixels.y){
                    roads.erase(roads.begin() + i);
                }
                i++;
            }
            this->roadBuilderHelper_->checkRoadsTexture(roads);
        

    }

    /**
     * Method responsible for deleting cameras from the map.
     * @param position - Position of camera to delete.
     * @param cameras - Table of cameras existing in the map view.
     * @param which_camera - Camera's to delete number.
     */
    void DeletingHelper::deleteCamera(sf::Vector2f position, sf::RectangleShape *cameras, int which_camera){
        sf::RectangleShape temp;

        
        if(this->camerasHelper_->checkCameraExists(this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y)), cameras)) { return; }

        for(int i = 0; i < 3; i++)
            if (cameras[i].getPosition().x == position.x && cameras[i].getPosition().y == position.y){
                cameras[which_camera-1] = temp;
            }
    }

}
