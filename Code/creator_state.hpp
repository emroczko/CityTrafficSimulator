#pragma once

#include <SFML/Graphics.hpp>
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

namespace ZPR{
    
    class CreatorState: public State{
    
    public:
        CreatorState (SimulatorDataRef data, int gridSize);
        CreatorState (SimulatorDataRef data, int gridSize, std::vector<Cell> Cells);
        void Init();  
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
    private:
        SimulatorDataRef _data;
        std::shared_ptr<MapView> _mapView;
        std::shared_ptr<ToolsView> _toolsView;
        std::shared_ptr<CamerasView> _camerasView;
        std::shared_ptr<CreatorHandler> _creatorHandler;
        std::shared_ptr<SimulationHandler> _simulationHandler;
        std::shared_ptr<CamerasSubject> _camerasSubject;
        int _gridSize;
        std::vector<Cell> _cells;
    };
}
