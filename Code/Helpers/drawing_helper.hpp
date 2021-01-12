/**
 * drawing_helper.hpp
 * Header of DrawingHelper class.
 */

#pragma once

#include "SFML/Graphics.hpp"
#include "../simulator.hpp"
#include "../Vehicles/vehicle.hpp"

namespace zpr {

    /**
     * Class responsible for help in drawing objects in the window.
     */
    class DrawingHelper{
    public:
        DrawingHelper(SimulatorDataRef data);
        void drawGrid(bool is_simulating, std::vector<sf::RectangleShape> grid_lines);
        void drawRoads(std::vector<sf::RectangleShape> roads);
        void drawVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles);
        void drawCameras(sf::RectangleShape *cameras);
        
    private:
        SimulatorDataRef data_;
    };
}
