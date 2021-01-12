/**
 * spawn_points.cpp
 * Implementation of SpawnPoints class.
 */

#include "spawn_points.hpp"

namespace zpr {
    /**
     * Parametrized constructor of SpawnPoints class.
     * @param grid_size - Size of the grid.
     */
    SpawnPoints::SpawnPoints(int grid_size): gridSize_(grid_size){
        this->converter_ = std::make_unique<Converter>(this->gridSize_);
        this->cellSize_ = this->converter_->getCellSize();
    }

    /**
     * Method which adds starting road to roads vector.
     */
    void SpawnPoints::addStartingRoad(std::vector<sf::RectangleShape>& roads) {
        int starting_cell_x[2];
        starting_cell_x[0] = 0;
        starting_cell_x[1] = this->gridSize_ - 1;
        for (int i = 0; i < 2; i++) {
            sf::RectangleShape road;
            road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
            road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
            sf::Vector2f centered_position_in_pixels = sf::Vector2f(starting_cell_x[i] * this->cellSize_ + this->converter_->calculatePrefix(), -2 * this->cellSize_ + this->converter_->calculatePrefix());
            centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2;
            centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2;
            road.setPosition(centered_position_in_pixels);
            roads.push_back(road);
        }
    }

    /**
     * Method which creates exit sites (for cars to leave city) in correct position
     */
    void SpawnPoints::setupExitSites(std::vector<sf::RectangleShape>& city_exit_site)
    {
        int exit_cell_x[2];
        exit_cell_x[0] = 0;
        exit_cell_x[1] = this->gridSize_ - 1;
        for (int i = 0; i < 2; i++) {
            sf::RectangleShape exit_site;
            exit_site.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, (SCREEN_HEIGHT / this->gridSize_) / 2));
            exit_site.setOrigin(sf::Vector2f(exit_site.getSize().x / 2, exit_site.getSize().y / 2));
            sf::Vector2f centered_position_in_pixels = sf::Vector2f(exit_cell_x[i] * this->cellSize_ + this->converter_->calculatePrefix(), -2 * this->cellSize_ + this->converter_->calculatePrefix());
            centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2;
            centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ * (2 * i + 1) / 4;
            exit_site.setPosition(centered_position_in_pixels);
            city_exit_site.push_back(exit_site);
        }
    }
}
