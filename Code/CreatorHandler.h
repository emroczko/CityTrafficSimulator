#pragma once
#include "CreatorSubject.h"
#include "Grid.h"
#include <memory>

namespace ZPR {
	class CreatorHandler : public CreatorSubject 
	{
	public:
		CreatorHandler(int gridSize);
		void init();
		void GenerateBoard();
		void HandleInput(sf::Vector2i possibleSelectedCell);
	private:
		std::unique_ptr<Grid> _grid;
		int _row, _col;
		int _gridSize;
	};
}

