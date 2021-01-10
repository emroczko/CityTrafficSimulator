/**
 * creator_state.hpp
 * Header of CreatorState class.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "state.hpp"
#include "simulator.hpp"
#include "button.hpp"
#include <vector>
#include "map_view.hpp"
#include "tools_view.hpp"
#include "cameras_view.hpp"
#include "creator_handler.hpp"
#include "keys_enum.hpp"
#include "simulation_handler.hpp"
#include "cell.hpp"

namespace zpr{
    /**
     * Class responsible for state with creating and simulating. It launches all observers and helper classes.
     */

    class CreatorState: public State{
    public:
        CreatorState (SimulatorDataRef data, int grid_size);
        CreatorState (SimulatorDataRef data, int grid_size, std::vector<Cell> cells);
        void init();
        void handleInput();
        void update(float dt);
        void draw(float dt);
        
    private:
        void handleKeyboard();
        SimulatorDataRef data_;
        std::shared_ptr<MapView> mapView_;
        std::shared_ptr<ToolsView> toolsView_;
        std::shared_ptr<CamerasView> camerasView_;
        std::shared_ptr<CreatorHandler> creatorHandler_;
        std::shared_ptr<SimulationHandler> simulationHandler_;
        std::shared_ptr<CamerasSubject> camerasSubject_;
        int gridSize_;
        std::vector<Cell> cells_;
    };
}
