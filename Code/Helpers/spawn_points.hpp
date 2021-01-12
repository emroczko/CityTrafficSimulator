/**
 * spawn_points.hpp
 * Header of SpawnPoints class.
 */

#pragma once
#include "SFML/Graphics.hpp"
#include "../definitions.hpp"
#include "converter.hpp"

namespace zpr {

    /**
     * Class responsible for setuping roads where vehicles start and end simulating. 
     */
    class SpawnPoints{
    public:
        SpawnPoints(int grid_size);
        void setupExitSites(std::vector<sf::RectangleShape>& city_exit_site);
        void addStartingRoad(std::vector<sf::RectangleShape>& roads);
    private:
        int gridSize_;
        int cellSize_;
        std::unique_ptr<Converter> converter_;
    };
}
