/**
 * converter.cpp
 * Implementation of Converter class.
 */
#include "converter.hpp"


namespace zpr {

    /**
     * Parametrized constructor of Converter class.
     * @param grid_size - Size of the grid.
     */
    Converter::Converter(int grid_size): gridSize_(grid_size){
        this->cellSize_ = (SCREEN_HEIGHT / this->gridSize_);
    }

    /**
     * Method responsible for converting pixels to rows or columns.
     * @param pixels - Value in pixels to convert.
     * @return - Converted value in rows or columns.
     */
    int Converter::transformPixelsToRowCol(double pixels){
        int result;
        
        if(pixels < 0)
            result = floor(pixels / this->cellSize_);
        else
            result = pixels / this->cellSize_;
        
        return result;
    }

    /**
     * Method responsible for converting coordinates from rows or columns to pixels.
     * @param rowcol - Row or column to convert.
     * @return - Converted value in pixels.
     */
    sf::Vector2f Converter::transformRowColToPixels(sf::Vector2i rowcol)
    {
        float x = rowcol.x * this->cellSize_ + this->calculatePrefix();
        float y = rowcol.y * this->cellSize_ + this->calculatePrefix();
        return sf::Vector2f(x, y);
    }
                                                   
   /**
    * Method responsible for calculating prefix - to drawing grid in the center of view.
    * @return - Calculated prefix.
    */
   int Converter::calculatePrefix() {
       double cell_size_with_point = (double)SCREEN_HEIGHT / gridSize_;
       double the_rest = cell_size_with_point - this->cellSize_;
       int draw_prefix = the_rest * gridSize_ / 2;
       return draw_prefix;
   }

}
