/**
 * adding_elements_map_view_helper.cpp
 * Implementation of AddingHelper class.
 */

#include "adding_elements_map_view_helper.hpp"
namespace zpr{

    /**
     * Parametrized constructor of AddingHelper class.
     * @param data - Struct containing data of current application. (eg. window, assets).
     * @param grid_size - Size of the grid in map view.
     */
    AddingHelper::AddingHelper(SimulatorDataRef data, int grid_size): data_(data), gridSize_(grid_size){
        this->roadBuilderHelper_ = std::make_unique<RoadBuilderHelper>(this->data_, this->gridSize_);
        this->converter_ = std::make_unique<Converter>(this->gridSize_);
        this->cellSize_ = this->converter_->getCellSize();
        this->camerasHelper_ = std::make_unique<CamerasHelper>(this->cellSize_);
    }
    /**
     * Method responsible for adding roads.
     * @param texture_name - Name of texture which should be added to road.
     * @param position - Position of road in row and column.
     * @return - RectangleShape object to be drawn and added.
     */
    sf::RectangleShape AddingHelper::addElement(std::string texture_name, sf::Vector2i position){
        sf::RectangleShape element;
        element.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
        element.setTexture(&this->data_->assets_.getTexture(texture_name));
        element.setOrigin(sf::Vector2f(element.getSize().x / 2, element.getSize().y / 2));
        sf::Vector2f centered_position_in_pixels = this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y));
        centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2 ;
        centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2 ;
        element.setPosition(centered_position_in_pixels);
        return element;
    }

    /**
     * Method responsible for adding cameras.
     * @param position - Position of camera in row and column.
     * @param cameras - Table of cameras exisiting in map view.
     * @param which_camera - Camera's to add number.
     */
    void AddingHelper::addCamera(sf::Vector2i position, sf::RectangleShape *cameras, int which_camera){
        if(this->camerasHelper_->checkCameraExists(this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y)), cameras)) {
            return ;
        }
        cameras[which_camera-1] = this->addElement("Camera", position);
    }

    
    /**
     * Method responsible for adding entry roads.
     * @param position - Position of road in row and column.
     * @param roads - Vector of roads existing in map view.
     */
    void AddingHelper::addEnterRoad(sf::Vector2i position, std::vector<sf::RectangleShape>& roads){
        roads.push_back(this->addElement("Road", position));
        this->roadBuilderHelper_->checkRoadsTexture(roads);
    }

    /**
     * Method responsible for adding garages (two entry points).
     * @param position - Position of garage in row and column.
     * @param roads - Vector of roads existing in map view.
     */
    void AddingHelper::addGarage(sf::Vector2i position, std::vector<sf::RectangleShape>& roads){
        roads.push_back(this->addElement("Entry", position));
    }


    /**
     * Method responsible for adding user roads.
     * @param position - Position of road in row and column.
     * @param roads - Vector of roads existing in map view.
     */
    void AddingHelper::addUserRoad(sf::Vector2i position, std::vector<sf::RectangleShape>& roads)
    {
        if(this->roadBuilderHelper_->checkRoadExists(this->converter_->transformRowColToPixels(sf::Vector2i(position.x, position.y)), roads)) {
            return;
        }
        roads.push_back(this->addElement("Road", position));
        this->roadBuilderHelper_->checkRoadsTexture(roads);
    }

}
