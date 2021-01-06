#pragma once
#include "CreatorSubject.h"
#include "Grid.h"
#include "ToolsObserver.h"
#include "SimulationObserver.h"
#include "CamerasObserver.h"
#include <memory>
#include "Vehicles/Vehicle.h"

namespace ZPR {
	class CreatorHandler : public CreatorSubject, public ToolsObserver, public CamerasObserver
	{
	public:
		CreatorHandler(int gridSize);
		void init();
		void GenerateBoard();
		void UpdateIsDrawingRoad();
        void UpdateIsDeletingRoad();
        void UpdateIsSimulating();
        void SaveToFile();
		void HandleInput(sf::Vector2i possibleSelectedCell);
		void UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles) {};
	private:
		std::unique_ptr<Grid> _grid;
		int _row, _col;
		int _gridSize;
        int _enterGridHeight;
		bool isDrawingRoad;
        bool isDeletingRoad;
        bool isSimulating;
	};
}

