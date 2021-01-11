//
//  road_builder_helper.cpp
//  CityTrafficSimulator
//
//  Created by Eryk Mroczko on 11/01/2021.
//

#include "road_builder_helper.hpp"


namespace zpr {

    RoadBuilderHelper::RoadBuilderHelper(SimulatorDataRef data, int grid_size): data_(data), gridSize_(grid_size){
        this->converter_ = std::make_unique<Converter>(this->gridSize_);
    }

    /**
     * Method responsible for checking wheter roads are set with correct textures in order to make drawn road look correct and properly.
     */
    void RoadBuilderHelper::checkRoadsTexture(std::vector<sf::RectangleShape>& roads) {
        for (sf::RectangleShape& road : roads) {
            std::shared_ptr<sf::RectangleShape> north = nullptr;
            std::shared_ptr<sf::RectangleShape> south = nullptr;
            std::shared_ptr<sf::RectangleShape> east = nullptr;
            std::shared_ptr<sf::RectangleShape> west = nullptr;
            std::vector<std::shared_ptr<sf::RectangleShape>> neighbouring_roads_ptr;
            int row = this->converter_->transformPixelsToRowCol(road.getPosition().y);
            int col = this->converter_->transformPixelsToRowCol(road.getPosition().x);
            for (sf::RectangleShape& neighbouring_road : roads) {
                int neighbouring_row = this->converter_->transformPixelsToRowCol(neighbouring_road.getPosition().y);
                int neighbouring_col = this->converter_->transformPixelsToRowCol(neighbouring_road.getPosition().x);
                if (row == neighbouring_row) {
                    if (col + 1 == neighbouring_col) {
                        east = std::make_shared<sf::RectangleShape>(neighbouring_road);
                        neighbouring_roads_ptr.push_back(east);
                    }
                    if (col - 1 == neighbouring_col) {
                        west = std::make_shared<sf::RectangleShape>(neighbouring_road);
                        neighbouring_roads_ptr.push_back(west);
                    }
                }
                if (col == neighbouring_col) {
                    if (row + 1 == neighbouring_row) {
                        south = std::make_shared<sf::RectangleShape>(neighbouring_road);
                        neighbouring_roads_ptr.push_back(south);
                    }
                    if (row - 1 == neighbouring_row) {
                        north = std::make_shared<sf::RectangleShape>(neighbouring_road);
                        neighbouring_roads_ptr.push_back(north);
                    }
                }
            }
            switch (neighbouring_roads_ptr.size()) {
            case 0: road.setTexture(&this->data_->assets_.getTexture("Road")); break;
            case 1: this->choseRoadWithOneNeighbour(road, north, south, east, west, row, col); break;
            case 2: this->choseRoadWithTwoNeighbours(road, north, south, east, west); break;
            case 3: this->choseRoadWithThreeNeighbours(road, north, south, east, west); break;
            case 4: road.setTexture(&this->data_->assets_.getTexture("Intersection")); break;
            }
        }
    }

    /**
     * Method responsible for setting correct texture for road in case when road has only one connected road.
     * @param road - Road whose texture will be set.
     * @param north - RectangleShape object representing road above our chosen road.
     * @param south - RectangleShape object representing road under our chosen road.
     * @param east - RectangleShape object representing road next to our chosen road (right cell).
     * @param west - RectangleShape object representing road next to our chosen road (left cell).
     * @param row - Current row.
     * @param col - Current column.
     */
    void RoadBuilderHelper::choseRoadWithOneNeighbour(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west, int row, int col){
        
        if (row != -2 && (col != 0 || col != gridSize_-1))
            road.setTexture(&this->data_->assets_.getTexture("Road"));
        
        road.setRotation(0);
        if (north)
            road.setRotation(90.f);
        else if (south)
            road.setRotation(90.f);
    }

    /**
     * Method responsible for setting correct texture for road in case when road has two connected roads.
     * @param road - Road whose texture will be set.
     * @param north - RectangleShape object representing road above our chosen road.
     * @param south - RectangleShape object representing road under our chosen road.
     * @param east - RectangleShape object representing road next to our chosen road (right cell).
     * @param west - RectangleShape object representing road next to our chosen road (left cell).
     */
    void RoadBuilderHelper::choseRoadWithTwoNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
    {
        road.setTexture(&this->data_->assets_.getTexture("Turn"));
        
        if (north && east)
            road.setRotation(0);
        
        else if (north && west)
            road.setRotation(270.f);
        
        else if (south && east)
            road.setRotation(90.f);
        
        else if (south && west)
            road.setRotation(180.f);
        
        else if (north && south){
            road.setTexture(&this->data_->assets_.getTexture("Road"));
            road.setRotation(90.f);
        }
        else if (east && west) {
            road.setTexture(&this->data_->assets_.getTexture("Road"));
            road.setRotation(0);
        }
    }

    /**
     * Method responsible for setting correct texture for road in case when road has three connected roads.
     * @param road - Road whose texture will be set.
     * @param north - RectangleShape object representing road above our chosen road.
     * @param south - RectangleShape object representing road under our chosen road.
     * @param east - RectangleShape object representing road next to our chosen road (right cell).
     * @param west - RectangleShape object representing road next to our chosen road (left cell).
     */
    void RoadBuilderHelper::choseRoadWithThreeNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
    {
        road.setTexture(&this->data_->assets_.getTexture("T_Intersection"));
        if (north && south && east)
            road.setRotation(0.f);
        else if (north && south && west)
            road.setRotation(180.f);
        
        else if (north && east && west)
            road.setRotation(270.f);
        
        else if (south && east && west)
            road.setRotation(90.f);
    }


}
