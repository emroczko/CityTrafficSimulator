#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Simulator.h"
#include "Button.h"

#include <vector>

#include "Button.h"
#include "MapView.h"
#include "ToolsView.h"
#include "CamerasView.h"
#include "CreatorHandler.h"
#include "SimulationHandler.h"


namespace ZPR{
    
    class CreatorState: public State{
    
    public:
        CreatorState (SimulatorDataRef data, int gridSize);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        
    private:
       
        
        SimulatorDataRef _data;
        std::shared_ptr<MapView> _mapView;
        std::shared_ptr<ToolsView> _toolsView;
        std::unique_ptr<CamerasView> _camerasView;
        std::shared_ptr<CreatorHandler> _creatorHandler;
        std::shared_ptr<SimulationHandler> _simulationHandler;
        int _gridSize;
    };
}
