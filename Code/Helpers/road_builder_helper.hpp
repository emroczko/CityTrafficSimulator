/**
 * road_builder_helper.hpp
 * Header of RoadBuilderHelper class.
 */


#pragma once

#include "SFML/Graphics.hpp"
#include "../simulator.hpp"
#include "converter.hpp"


namespace zpr {

    /**
     * Class responsible for helping adding textures for roads in map view and checking if certain roads exist.
     */
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
