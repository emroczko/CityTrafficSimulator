#pragma once
#include <SFML/Graphics.hpp>
namespace ZPR {
	class Cell
	{
	public:
		Cell(int row, int column);
		Cell();
		sf::Vector2i GetPosition();
        bool _containsRoad, _toDelete, _roadDrawn;
        bool _north, _south, _east, _west;
	private:
		int _row, _column;
	};
}

