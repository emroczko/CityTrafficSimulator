#pragma once
#include <SFML/Graphics.hpp>
namespace ZPR {
	class Cell
	{
	public:
		Cell(int row, int column);
		sf::Vector2i GetPosition();
        bool _containsRoad, _toDelete, _roadDrawn, isStartingCell;
	private:
		int _row, _column;
	};
}

