/**
 * adding_elements_map_view_helper.hpp
 * Header of AddingHelper class.
 */

#pragma once

#include "SFML/Graphics.hpp"
#include "simulator.hpp"
#include "converter.hpp"
#include "road_builder_helper.hpp"
#include "cameras_map_view_helper.hpp"
#include "definitions.hpp"

namespace zpr {

    /**
     * Class responsible for adding sf::RectangleShape objects to map view (roads and cameras).
     */
    class AddingHelper{
    public:
        AddingHelper(SimulatorDataRef data, int grid_size);
        sf::RectangleShape addElement(std::string fileName, sf::Vector2i position);
        void addUserRoad(sf::Vector2i position, std::vector<sf::RectangleShape>& roads);
        void addGarage(sf::Vector2i position, std::vector<sf::RectangleShape>& roads);
        void addEnterRoad(sf::Vector2i position, std::vector<sf::RectangleShape>& roads);
        void addCamera(sf::Vector2i position, sf::RectangleShape *cameras, int which_camera);
    private:
        SimulatorDataRef data_;
        int gridSize_, cellSize_;
        std::unique_ptr<Converter> converter_;
        std::unique_ptr<RoadBuilderHelper> roadBuilderHelper_;
        std::unique_ptr<CamerasHelper> camerasHelper_;
    };
}
