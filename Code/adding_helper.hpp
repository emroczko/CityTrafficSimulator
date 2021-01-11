//
//  adding_helper.hpp
//  CityTrafficSimulator
//
//  Created by Eryk Mroczko on 11/01/2021.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "simulator.hpp"
#include "converter.hpp"
#include "road_builder_helper.hpp"

namespace zpr {

    class AddingHelper{
    public:
        AddingHelper(SimulatorDataRef data, int grid_size);
        sf::RectangleShape addRoad(std::string fileName, sf::Vector2i position);
        void addUserRoad(sf::Vector2i position, std::vector<sf::RectangleShape>& roads);
        void addGarage(sf::Vector2i position, std::vector<sf::RectangleShape>& roads);
        void addEnterRoad(sf::Vector2i position, std::vector<sf::RectangleShape>& roads);
        //void addCamera(sf::Vector2i position);
    private:
        SimulatorDataRef data_;
        int gridSize_, cellSize_;
        std::unique_ptr<Converter> converter_;
        std::unique_ptr<RoadBuilderHelper> roadBuilderHelper_;
    };
}