/**
 * cell.hpp
 * Header of Cell class.
 */

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
namespace zpr {

    /**
     * Class responsible for single cell and its attributes.
     */
	class Cell
	{
	public:
		Cell(int row, int column);
        Cell();
		sf::Vector2i getPosition();
        bool containsRoad_, toDelete_, roadDrawn_, isStartingCell_, containsCamera_, cameraDrawn_, cameraToDelete_;
        int whichCamera_;
        std::istream& load(std::istream& is);
        friend std::istream& operator>> (std::istream&, Cell&);
        friend std::ofstream& operator<< (std::ofstream&, const Cell&);
        friend std::ostream& operator<< (std::ostream&, const Cell&);
    private:
		int row_, column_;
        
	};
}

