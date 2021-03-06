/**
 * creator_handler.hpp
 * Header of CreatorHandler class.
 */


#pragma once
#include "subjects/creator_subject.hpp"
#include "components/grid.hpp"
#include "observers/tools_observer.hpp"
#include "observers/simulation_observer.hpp"
#include "observers/cameras_observer.hpp"
#include <memory>
#include "vehicles/vehicle.hpp"

namespace zpr {

    /**
     * Class responsible for handle creating and deleting roads. Also it handles save button. 
     */
	class CreatorHandler : public CamerasObserver, public CreatorSubject, public ToolsObserver
	{
	public:
		CreatorHandler(int grid_size);
        CreatorHandler(int grid_size, std::vector<Cell> cells);
		void init();
		void generateBoard();
        void generateEnterBoard();
        void clearRoads();
		void updateIsDrawingRoad();
        void updateIsDeletingRoad();
        void updateIsSimulating();
        void updateIsAddingCamera(int which_camera);
        void updateIsDeletingCamera(int which_camera);
        void saveToFile();
		void handleInput(sf::Vector2i possible_selected_cell);
	private:
		std::unique_ptr<Grid> grid_, enterGrid_;
        std::vector<Cell> cells_;
		int row_, col_;
		int gridSize_;
        int enterGridHeight_;
        int whichCamera_;
		bool isDrawingRoad_;
        bool isDeletingRoad_;
        bool isSimulating_;
        bool isAddingCameras_;

	};
}

