#include "Cell.h"

namespace ZPR {
Cell::Cell(int row, int column) : _row(row), _column(column), _containsRoad(false), _toDelete(false){
    }

	sf::Vector2i Cell::GetPosition()
	{
		return sf::Vector2i(this->_row, this->_column);
	}
}
