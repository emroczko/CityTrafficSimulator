//
//  road_builder_helper.hpp
//  CityTrafficSimulator
//
//  Created by Eryk Mroczko on 11/01/2021.
//
#pragma once

#include "SFML/Graphics.hpp"
#include "simulator.hpp"
#include "converter.hpp"


namespace zpr {

    class RoadBuilderHelper{
    public:
        RoadBuilderHelper(SimulatorDataRef data, int grid_size);
        void checkRoadsTexture(std::vector<sf::RectangleShape>& roads);
        bool checkRoadExists(sf::Vector2f position, std::vector<sf::RectangleShape>& roads);
    private:
        void choseRoadWithOneNeighbour(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
            std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west, int row, int col);
        void choseRoadWithTwoNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
            std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
        void choseRoadWithThreeNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
            std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
        
        SimulatorDataRef data_;
        std::unique_ptr<Converter> converter_;
        int gridSize_;
        int cellSize_;
    };
}
