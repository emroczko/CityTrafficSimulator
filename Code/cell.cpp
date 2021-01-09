#include "cell.hpp"

#include <iostream>
#include <fstream>
 

namespace ZPR {
	Cell::Cell(int row, int column) : _row(row), _column(column), _containsRoad(false), _toDelete(false), _roadDrawn(false), isStartingCell(false), _containsCamera(false), _cameraDrawn(false), _cameraToDelete(false), _whichCamera(0){}
    Cell::Cell(): _row(0), _column(0), _containsRoad(false), _toDelete(false), _roadDrawn(false), isStartingCell(false), _containsCamera(false), _cameraDrawn(false),_cameraToDelete(false), _whichCamera(0){}

	/*Zwraca pozycjê komórki reprezentowan¹ za pomoca numeru wiersza i kolumny*/
	sf::Vector2i Cell::GetPosition()
	{
		return sf::Vector2i(this->_row, this->_column);
	}
    std::istream& Cell::load(std::istream &in){
        in >> _row >> _column >> _containsRoad;
        return in;
    }
    std::istream & operator>> (std::istream &in, Cell& currentCell)
    {
        return currentCell.load(in);
    }
    std::ofstream& operator<< (std::ofstream& os, const Cell& currentCell){
        os << currentCell._row <<" "<< currentCell._column<<" "<<currentCell._containsRoad<<std::endl;
        return os;
    }
    std::ostream& operator<< (std::ostream& os, const Cell& currentCell){
        os << currentCell._row <<" "<< currentCell._column<<" "<<currentCell._containsRoad<<std::endl;
        return os;
    }


}
