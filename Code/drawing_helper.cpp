/**
 * drawing_helper.cpp
 * Implementation of DrawingHelper class.
 */

#include "drawing_helper.hpp"

namespace zpr{

    /**
     * Parametrized constructor of DrawingHelper class.
     * @param data - Struct containing data of current application. (eg. window, assets)
     */
    DrawingHelper::DrawingHelper(SimulatorDataRef data): data_(data){
        
    }
    /**
     * Method responsible for drawing grid on the map.
     * @param is_simulating - Value telling if simulation is taking place.
     * @param grid_lines - sf::RectangleShape objects representing lines of grid.
     */
    void DrawingHelper::drawGrid(bool is_simulating, std::vector<sf::RectangleShape> grid_lines) {
        if(!is_simulating){
            for (sf::RectangleShape line : grid_lines) {
                this->data_->window_.draw(line);
            }
        }
    }

    /**
     * Method responsible for drawing roads made by user.
     * @param roads - Vector of roads existing in map view.
     */
    void DrawingHelper::drawRoads(std::vector<sf::RectangleShape> roads){
        for (sf::RectangleShape road : roads) {
            this->data_->window_.draw(road);
        }
    }

    /**
     * Method responsible for drawing vehicles.
     * @param vehicles - Vector of vehicles existing in map view.
     */

    void DrawingHelper::drawVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles)
    {
        for (std::shared_ptr<Vehicle>& vehicle : vehicles) {
            this->data_->window_.draw(*vehicle);
        }

    }

    /**
     * Method responsible for drawing cameras.
     * @param cameras - Table of cameras existing in map view.
     */
    void DrawingHelper::drawCameras(sf::RectangleShape *cameras){
        for (int i = 0; i<3; i++) {
            this->data_->window_.draw(cameras[i]);
        }
    }

}
