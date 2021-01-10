/**
 * cell.cpp
 * Implementation of Cell class.
 */

#include "cell.hpp"
#include <iostream>
#include <fstream>
 

namespace zpr {


    /**
     * Default constructor of Cell class.
     */
    Cell::Cell(): row_(0), column_(0), containsRoad_(false), toDelete_(false), roadDrawn_(false), isStartingCell_(false), containsCamera_(false), cameraDrawn_(false), cameraToDelete_(false), whichCamera_(0){}

    /**
     * Parametrized constructor of Cell class.
     * @param row - Row on which cell should be.
     * @param column - Column on which cell should be.
     */
	Cell::Cell(int row, int column) : row_(row), column_(column), containsRoad_(false), toDelete_(false), roadDrawn_(false), isStartingCell_(false), containsCamera_(false), cameraDrawn_(false), cameraToDelete_(false), whichCamera_(0){}

    /**
     * Method returning cell position with row and column.
     * @return - Cell position presented by row and column.
     */
	sf::Vector2i Cell::getPosition()
	{
		return sf::Vector2i(this->row_, this->column_);
	}
    
    /**
     * Method handling data from istream.
     * @param in - Istream from which data is taken.
     * @return - Istream to which data is passed.
     */
    std::istream& Cell::load(std::istream &in){
        in >> row_ >> column_ >> containsRoad_;
        return in;
    }

    /**
     * Overloaded operator >> loading data from istream.
     * @param in - Istream from which data is taken.
     * @param current_cell - Current cell to which data is passed.
     * @return - Istream to which data is passed.
     */
    std::istream & operator>> (std::istream &in, Cell& current_cell)
    {
        return current_cell.load(in);
    }

    /**
     * Overloaded operator << printing current cell to ofstream.
     * @param os - Ofstream object.
     * @param current_cell - Current cell which is being printed.
     * @return - Ofstream to where data is passed.
     */
    std::ofstream& operator<< (std::ofstream& os, const Cell& current_cell){
        os << current_cell.row_ <<" "<< current_cell.column_<<" "<<current_cell.containsRoad_<<std::endl;
        return os;
    }

    /**
     * Overloaded operator << printing current cell to ostream.
     * @param os - Ofstream object.
     * @param current_cell - Current cell which is being printed.
     * @return - Ofstream to where data is passed.
     */
    std::ostream& operator<< (std::ostream& os, const Cell& current_cell){
        os << current_cell.row_ <<" "<< current_cell.column_<<" "<<current_cell.containsRoad_<<std::endl;
        return os;
    }


}
