#include "Cell.h"

#include <iostream>
#include <fstream>
 

namespace ZPR {
	Cell::Cell(int row, int column) : _row(row), _column(column), _containsRoad(false), _toDelete(false), _roadDrawn(false), isStartingCell(false){}


	/*Zwraca pozycjê komórki reprezentowan¹ za pomoca numeru wiersza i kolumny*/
	sf::Vector2i Cell::GetPosition()
	{
		return sf::Vector2i(this->_row, this->_column);
	}

    std::ofstream& operator<< (std::ofstream& os, const Cell& currentCell){
        os << currentCell._row <<" & "<< currentCell._column<<" % "<<currentCell._containsRoad<<std::endl;
        return os;
    }
    std::ostream& operator<< (std::ostream& os, const Cell& currentCell){
        os << currentCell._row <<" & "<< currentCell._column<<" % "<<currentCell._containsRoad<<std::endl;
        return os;
    }

}
