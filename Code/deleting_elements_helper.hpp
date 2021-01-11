/**
 * deleting_elements_helper.hpp
 * Header of DeletingHelper class.
 */
#pragma once

#include "SFML/Graphics.hpp"
#include "simulator.hpp"
#include "converter.hpp"
#include "road_builder_helper.hpp"
#include "cameras_map_view_helper.hpp"

namespace zpr {

    /**
     * Class responsible for deleting sf::RectangleShapes from mapView (cameras and roads).
     */
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
        std::unique_ptr<CamerasHelper> camerasHelper_;
    };
}

