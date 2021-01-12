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

    /**
     * Method responsible for returning cell size.
     * @return - Cell size.
     */
    int Converter::getCellSize(){
        return this->cellSize_;
    }


    /**
     * Method which converts Cell object to sf::RectangleShape object.
     * @param cell - Cell to convert.
     * @param which_road - Information if we are converting enter cells or user cells. 
     * @return - Converted sf::RectangleShape object.
     */
    sf::RectangleShape Converter::convertCellToCenteredRectShape(Cell cell, std::string which_road)
    {
        sf::RectangleShape rect_shape;
        rect_shape.setSize(sf::Vector2f(SCREEN_HEIGHT / this->gridSize_, SCREEN_HEIGHT / this->gridSize_));
        rect_shape.setOrigin(sf::Vector2f(rect_shape.getSize().x / 2, rect_shape.getSize().y / 2));
        sf::Vector2f centered_position_in_pixels;
        if(which_road == "User" ){
            centered_position_in_pixels = sf::Vector2f(cell.getPosition().x * this->cellSize_ + this->calculatePrefix(), cell.getPosition().y * this->cellSize_ + this->calculatePrefix());
        }
        else{
            centered_position_in_pixels = sf::Vector2f(cell.getPosition().y * this->cellSize_ + this->calculatePrefix(), cell.getPosition().x * this->cellSize_ + this->calculatePrefix());
        }
                                     
        centered_position_in_pixels.x = centered_position_in_pixels.x + this->cellSize_ / 2;
        centered_position_in_pixels.y = centered_position_in_pixels.y + this->cellSize_ / 2;
        rect_shape.setPosition(centered_position_in_pixels);
        return rect_shape;
    }

}
