#pragma once
#include "cell.hpp"
#include "Vehicles/vehicle.hpp"
namespace ZPR {
	class CreatorObserver
	{
	public:
		virtual void UpdateSelectedCell(sf::Vector2i coords) = 0;
		virtual void UpdateCells(std::vector<Cell> cells) = 0;
        virtual void SaveToFile() = 0;
		virtual void UpdateIsDrawingRoad(bool isDrawingRoad) = 0;
        virtual void UpdateIsDeletingRoad(bool isDeletingRoad) = 0;
        virtual void UpdateIsAddingCamera(bool isAddingCamera, int whichCamera, int row, int col) = 0;
        virtual void UpdateIsDeletingCamera(int whichCamera) = 0;
		virtual ~CreatorObserver() {}
	};
}

