//
//  delete_road_helper.hpp
//  CityTrafficSimulator
//
//  Created by Eryk Mroczko on 11/01/2021.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "simulator.hpp"
#include "converter.hpp"
#include "road_builder_helper.hpp"
#include "cameras_map_view_helper.hpp"

namespace zpr {

    class DeletingHelper{
    public:
        DeletingHelper(SimulatorDataRef data, int grid_size);
        void deleteRoad(sf::Vector2f position, std::vector<sf::RectangleShape>& roads);
        void deleteCamera(sf::Vector2f position, sf::RectangleShape *cameras, int which_camera);
    private:
        SimulatorDataRef data_;
        int gridSize_, cellSize_;
        std::unique_ptr<Converter> converter_;
        std::unique_ptr<RoadBuilderHelper> roadBuilderHelper_;
        std::shared_ptr<CamerasHelper> camerasHelper_;
    };
}

