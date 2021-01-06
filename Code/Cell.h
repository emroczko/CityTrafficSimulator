#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
namespace ZPR {
	class Cell
	{
	public:
		Cell(int row, int column);
		sf::Vector2i GetPosition();
        bool _containsRoad, _toDelete, _roadDrawn, isStartingCell;
        friend std::ofstream& operator<< (std::ofstream& ,const Cell&);
        friend std::ostream& operator<< (std::ostream& ,const Cell&);
    private:
		int _row, _column;
        
	};
}

