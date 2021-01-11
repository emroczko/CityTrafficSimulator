//
//  adding_helper.cpp
//  CityTrafficSimulator
//
//  Created by Eryk Mroczko on 11/01/2021.
//

#include "adding_helper.hpp"
namespace zpr{
    AddingHelper::AddingHelper(SimulatorDataRef data, int grid_size): data_(data), gridSize_(grid_size){
        this->roadBuilderHelper_ = std::make_unique<RoadBuilderHelper>(this->data_, this->gridSize_);
        this->converter_ = std::make_unique<Converter>(this->gridSize_);
        this->cellSize_ = (SCREEN_HEIGHT / this->gridSize_);
    }
    /**
     * Method responsible for adding roads.
     * @param texture_name - Name of texture which should be added to road.
     * @param position - Position of road in row and column.
     */
    sf::RectangleShape AddingHelper::addRoad(std::string texture_name, sf::Vector2i position){
        sf::RectangleShape road;
        road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
        road.setTexture(&this->data_->assets_.getTexture(texture_name));
        road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
        sf::Vector2f centered_position_in_pixels = this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y));
        centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2 ;
        centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2 ;
        road.setPosition(centered_position_in_pixels);
        //this->roads_.push_back(road);
        return road;
    }

//    /**
//     * Method responsible for adding cameras.
//     * @param position - Position of camera in row and column.
//     */
//    void AddingHelper::addCamera(sf::Vector2i position){
//        //if (this->checkCameraExists(this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y)))) { return; }
//        
//        sf::RectangleShape camera;
//        camera.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
//        camera.setTexture(&this->data_->assets_.getTexture("Camera"));
//        camera.setOrigin(sf::Vector2f(camera.getSize().x / 2, camera.getSize().y / 2));
//        sf::Vector2f centered_position_in_pixels = this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y));
//        centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2 ;
//        centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2 ;
//        camera.setPosition(centered_position_in_pixels);
//        //this->cameras_[whichCamera_-1] = camera;
//    }

    /**
     * Method responsible for adding entry roads.
     * @param position - Position of road in row and column.
     */
    void AddingHelper::addEnterRoad(sf::Vector2i position, std::vector<sf::RectangleShape>& roads){
        roads.push_back(this->addRoad("Road", position));
        this->roadBuilderHelper_->checkRoadsTexture(roads);
    }

    /**
     * Method responsible for adding garages (two entry points).
     * @param position - Position of garage in row and column.
     */
    void AddingHelper::addGarage(sf::Vector2i position, std::vector<sf::RectangleShape>& roads){
        roads.push_back(this->addRoad("Entry", position));
    }


    /**
     * Method responsible for adding user roads.
     * @param position - Position of road in row and column.
     */
    void AddingHelper::addUserRoad(sf::Vector2i position, std::vector<sf::RectangleShape>& roads)
    {
        if(this->roadBuilderHelper_->checkRoadExists(this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y)), roads)) {
            return;
        }
        roads.push_back(this->addRoad("Road", position));
        this->roadBuilderHelper_->checkRoadsTexture(roads);
    }

}
