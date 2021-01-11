//
//  delete_road_helper.cpp
//  CityTrafficSimulator
//
//  Created by Eryk Mroczko on 11/01/2021.
//

#include "deleting_elements_helper.hpp"

namespace zpr {

    DeletingHelper::DeletingHelper(SimulatorDataRef data, int grid_size): data_(data), gridSize_(grid_size){
        this->roadBuilderHelper_ = std::make_unique<RoadBuilderHelper>(this->data_, this->gridSize_);
        this->converter_ = std::make_unique<Converter>(this->gridSize_);
        this->cellSize_ = (SCREEN_HEIGHT / this->gridSize_);
        this->camerasHelper_ = std::make_unique<CamerasHelper>(this->cellSize_);
    }

    /**
     * Method responsible for deleting roads from the map.
     * @param position - Position of the road in row and column.
     */
    void DeletingHelper::deleteRoad(sf::Vector2f position, std::vector<sf::RectangleShape> &roads){

            int i = 0;

            if(this->roadBuilderHelper_->checkRoadExists(this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y)), roads)) { return; }
            
            for (sf::RectangleShape road : roads) {
                if (road.getPosition().x - this->cellSize_ / 2 == position.x && road.getPosition().y - this->cellSize_ / 2 == position.y){
                    roads.erase(roads.begin() + i);
                }
                i++;
            }
            this->roadBuilderHelper_->checkRoadsTexture(roads);
        

    }

    /**
     * Method responsible for deleting cameras from the map.
     * @param position - Position of camera to delete.
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
