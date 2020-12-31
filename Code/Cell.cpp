#include "Cell.h"

namespace ZPR {
	Cell::Cell(int row, int column) : _row(row), _column(column), _containsRoad(false), _toDelete(false), _north(false), _south(false), _east(false),_west(false), _roadDrawn(false){}
	/*Zwraca pozycjê komórki reprezentowan¹ za pomoca numeru wiersza i kolumny*/
	sf::Vector2i Cell::GetPosition()
	{
		return sf::Vector2i(this->_row, this->_column);
	}
}
