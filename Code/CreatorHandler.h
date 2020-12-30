#pragma once
#include "CreatorSubject.h"
#include "Grid.h"
#include "ToolsObserver.h"
#include "SimulationObserver.h"
#include <memory>

namespace ZPR {
	class CreatorHandler : public CreatorSubject, public ToolsObserver, public SimulationObserver
	{
	public:
		CreatorHandler(int gridSize);
		void init();
		void GenerateBoard();
		//void AddCellsRef(std::vector<Cell>* cells);
		void UpdateIsDrawingRoad();
        void UpdateIsDeletingRoad();
        void UpdateIsSimulating(bool isSimulating);
		void HandleInput(sf::Vector2i possibleSelectedCell);
	private:
		std::unique_ptr<Grid> _grid;
		int _row, _col;
		int _gridSize;
		bool isDrawingRoad;
        bool isDeletingRoad;
        bool isSimulating;
	};
}

