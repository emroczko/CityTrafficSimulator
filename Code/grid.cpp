#include "grid.hpp"

namespace ZPR {

	Grid::Grid(std::vector<Cell> cells, int size): _cells(cells), _size(size) {}
	

    Grid::Grid(std::vector<Cell> cells, int width, int height): _cells(cells), _height(height), _width(width) {}
	/*Zwraca referencjê do komórki na konkretnej pozycji reprezentowanej przez numer wiersza i kolumny*/
	Cell& Grid::GetCell(int row, int column)
	{
		return this->_cells.at(row * _size + column);
	}
}
