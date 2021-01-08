#pragma once
#include "CreatorSubject.h"
#include "Grid.h"
#include "ToolsObserver.h"
#include "SimulationObserver.h"
#include "CamerasObserver.h"
#include <memory>
#include "Vehicles/Vehicle.h"

namespace ZPR {
	class CreatorHandler : public CamerasObserver, public CreatorSubject, public ToolsObserver
	{
	public:
		CreatorHandler(int gridSize);
        CreatorHandler(int gridSize, std::vector<Cell> cells);
		void init();
		void GenerateBoard();
        void ClearRoads();
		void UpdateIsDrawingRoad();
        void UpdateIsDeletingRoad();
        void UpdateIsSimulating();
        void UpdateIsAddingCamera(int whichCamera);
        void UpdateIsDeletingCamera(int whichCamera);
        void SaveToFile();
		void HandleInput(sf::Vector2i possibleSelectedCell);
		void UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) {};
	private:
		std::unique_ptr<Grid> _grid;
        std::vector<Cell> _cells;
		int _row, _col;
		int _gridSize;
        int _enterGridHeight;
        int _whichCamera;
		bool _isDrawingRoad;
        bool _isDeletingRoad;
        bool _isSimulating;
        bool _isAddingCameras;
        
	};
}

