#include "Cell.h"

namespace ZPR {
	Cell::Cell(int row, int column) : _row(row), _column(column), _containsRoad(false), _toDelete(false), _north(false), _south(false), _east(false),_west(false) /*, north(nullptr), south(nullptr), east(nullptr), west(nullptr)*/{}
	Cell::Cell() {}
	sf::Vector2i Cell::GetPosition()
	{
		return sf::Vector2i(this->_row, this->_column);
	}
}
