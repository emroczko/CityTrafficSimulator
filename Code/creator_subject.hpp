#pragma once
#include "creator_observer.hpp"
#include "cell.hpp"
#include <vector>

namespace zpr {
	class CreatorSubject
	{
	public:
		void add(std::shared_ptr<CreatorObserver> observer);
		void notifySelectedCell(sf::Vector2i coords);
		void notifyCells(std::vector<Cell> cells);
        void notifySave();
		void notifyIsDrawingRoad(bool is_drawing_road);
        void notifyIsAddingCamera(bool is_adding_camera, int which_camera);
        void notifyCameraAdded(int which_camera, int row, int col);
        void notifyIsDeletingCamera(int which_camera);
        void notifyIsDeletingRoad(bool is_deleting_road);
        void notifyIsSimulating(bool is_simulating);
		virtual ~CreatorSubject() {}
        
	private:
		std::vector<std::shared_ptr<CreatorObserver> > observers_;
	};
}

