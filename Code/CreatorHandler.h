#pragma once
#include "CreatorSubject.h"
#include "Grid.h"
#include "ToolsObserver.h"
#include "SimulationObserver.h"
#include <memory>
#include "Vehicles/Vehicle.h"

namespace ZPR {
	class CreatorHandler : public CreatorSubject, public ToolsObserver, public SimulationObserver
	{
	public:
		CreatorHandler(int gridSize);
		void init();
		void GenerateBoard();
		void UpdateIsDrawingRoad();
        void UpdateIsDeletingRoad();
        void UpdateIsSimulating(bool isSimulating);
		void HandleInput(sf::Vector2i possibleSelectedCell);
	private:
		std::unique_ptr<Grid> _grid;
		std::vector<std::shared_ptr<Vehicle>> _vehicles;
		int _row, _col;
		int _gridSize;
		bool isDrawingRoad;
        bool isDeletingRoad;
        bool isSimulating;
	};
}

