#pragma once
#include <SFML/Graphics.hpp>
namespace ZPR {
	class Cell
	{
	public:
		Cell(int row, int column);
		Cell();
		sf::Vector2i GetPosition();
        bool _containsRoad, _toDelete;
		/*WskaŸniki do komórek góra, dó³, prawo lewo
		std::shared_ptr<Cell> north;
		std::shared_ptr<Cell> south;
		std::shared_ptr<Cell> east;
		std::shared_ptr<Cell> west;*/
        bool _north, _south, _east, _west;
	private:
		int _row, _column;
	};
}

