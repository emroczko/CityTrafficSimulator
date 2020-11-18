#include "Cell.h"

namespace ZPR {
	Cell::Cell(int row, int column) : _row(row), _column(column) {}

	sf::Vector2f Cell::GetPosition()
	{
		return sf::Vector2f(this->_row, this->_column);
	}
}
