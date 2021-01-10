/**
 * creator_observer.hpp
 * Header of CreatorObserver virtual class.
 */


#pragma once
#include "cell.hpp"
#include "Vehicles/vehicle.hpp"
namespace zpr {

    /**
     * Virtual class responsible for being an observer for CreatorHandler class.
     */
	class CreatorObserver
	{
	public:
		virtual void updateSelectedCell(sf::Vector2i coords) = 0;
		virtual void updateCells(std::vector<Cell> cells) = 0;
        virtual void saveToFile() = 0;
		virtual void updateIsDrawingRoad(bool is_drawing_road) = 0;
        virtual void updateIsDeletingRoad(bool is_deleting_road) = 0;
        virtual void updateIsAddingCamera(bool is_adding_camera, int which_camera) = 0;
        virtual void updateCameraAdded(int which_camera, int row, int col) = 0;
        virtual void updateIsDeletingCamera(int which_camera) = 0;
		virtual ~CreatorObserver() {}
	};
}

