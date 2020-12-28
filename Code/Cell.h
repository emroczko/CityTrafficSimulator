#pragma once
#include <SFML/Graphics.hpp>
namespace ZPR {
	class Cell
	{
	public:
		Cell(int row, int column);
		sf::Vector2i GetPosition();
        bool _containsRoad, _toDelete;
        bool north, east, south, west;
	private:
		int _row, _column;
        
	};
}

