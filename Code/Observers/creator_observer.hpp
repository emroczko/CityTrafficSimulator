/**
 * creator_observer.hpp
 * Header of CreatorObserver virtual class.
 */


#pragma once
#include "../components/cell.hpp"
#include "../vehicles/vehicle.hpp"
namespace zpr {

    /**
     * Virtual class responsible for being an observer for CreatorHandler class.
     */
	class CreatorObserver
	{
	public:
        virtual void updateSelectedCell(sf::Vector2i coords) {}
        virtual void updateCells(std::vector<Cell> cells) {}
        virtual void updateEnterCells(std::vector<Cell> enter_cells) {}
        virtual void saveToFile() {}
        virtual void updateIsDrawingRoad(bool is_drawing_road) {}
        virtual void updateIsDeletingRoad(bool is_deleting_road) {}
        virtual void updateIsAddingCamera(bool is_adding_camera, int which_camera) {}
        virtual void updateCameraAdded(int which_camera, int row, int col) {}
        virtual void updateIsDeletingCamera(int which_camera) {}
		virtual ~CreatorObserver() {}
	};
}

