#pragma once
#include <SFML/Graphics.hpp>
namespace ZPR {
	class Cell
	{
	public:
		Cell(int row, int column);
		sf::Vector2i GetPosition();
		bool _containsRoad;
	private:
		int _row, _column;
		
	};
}

