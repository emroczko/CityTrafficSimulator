/**
 * map_view.hpp
 * Header for MapView class.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "simulator.hpp"
#include "button.hpp"
#include "definitions.hpp"
#include <vector>
#include "creator_observer.hpp"
#include "simulation_observer.hpp"
#include "simulation_handler.hpp"
#include "keys_enum.hpp"


namespace zpr {
    /**
     * Class responsible for drawing map, grids, vehicles, cameras and handling events in map.
     */
	class MapView : public CreatorObserver, public SimulationObserver
	{
	public:
		MapView(SimulatorDataRef data, int grid_size);
        MapView(const MapView& map_view);
		void updateSelectedCell(sf::Vector2i coords);
		void updateCells(std::vector<Cell> cells);
        void updateRoads(std::vector<sf::RectangleShape> roads);
		void updateIsDrawingRoad(bool is_drawing_road);
        void updateIsDeletingRoad(bool is_deleting_road);
        void updateIsSimulating(bool is_simulating);
        void updateIsAddingCamera(bool is_adding_camera, int which_camera);
        void updateCameraAdded(int which_camera, int row, int col);
        void UpdateIsAddingCamera(int which_camera);
        void updateIsDeletingCamera(int which_camera);
        void updateCarsLabel(int which_label){}
        void updateTrucksLabel(int which_label){}
        void saveToFile();
		void updateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles);
		void draw();
		sf::Vector2i handleInput(sf::Vector2f mousePosition);
        sf::View getView();
		void init();
		sf::Vector2i getRowCol();
		bool isClicked(sf::Vector2i mousePosition);
        void move(keysEnum key);
		int getGridSize();
		int getCellSize();
        std::vector<Cell> getCells();
        void zoomViewAt(float zoom);
        friend std::ofstream& operator<< (std::ofstream& ,const MapView&);
        friend std::ostream& operator<< (std::ostream& ,const MapView&);
	private:
        
        
		void loadAssets();
		sf::FloatRect calculateViewPort();
		void drawGrid();
        void drawEnterGrid();
		void drawRoads();
        void drawEntryRoads();
		void drawVehicles();
        void drawCameras();
		void generateGridLines();
        void generateEnterGridLines();
        void generateEnterBoard();
		int calculatePrefix();
		void fillCells();
        void fillEnterCells();
        void addRoad(std::string fileName, sf::Vector2i position);
		void addUserRoad(sf::Vector2i position);
        void addGarage(sf::Vector2i position);
        void addEnterRoad(sf::Vector2i position);
        void addCamera(sf::Vector2i position);
		void checkRoadsTexture();
		void choseRoadWithOneNeighbour(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
			std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west, int row, int col);
		void choseRoadWithTwoNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
			std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void choseRoadWithThreeNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
			std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
        void deleteRoad(sf::Vector2f position);
        void deleteCamera(sf::Vector2f position);
		bool checkRoadExists(sf::Vector2f position);
        bool checkCameraExists(sf::Vector2f position);
		sf::Vector2f transformRowColToPixels(sf::Vector2i rowcol);
        int transformPixelsToRowCol(double pixels);
        void setupSelectedCellRect();
        void initializeCameras();
        
        
        bool clicked_;
        std::unique_ptr<Grid> enterGrid_;
        int maximumZoom_;
		SimulatorDataRef data_;
		int gridSize_;
		int cellSize_;
        int whichCamera_;
		int row_, col_;
        int enterGridHeight_;
        int enterGridWidth_;
		bool isDrawingRoad_;
        bool isDeletingRoad_;
        bool isSimulating_;
        bool isAddingCamera_;
        sf::Vector2i buffer_;
		sf::RectangleShape selectedCellRect_;
		std::vector<sf::RectangleShape> gridLines_;
        std::vector<sf::RectangleShape> enterGridLines_;
		sf::Sprite backgroundTexture_;
		sf::View mapView_;
        std::vector<sf::RectangleShape> roads_, entryRoad_, cameras_;
        sf::RectangleShape camerasT_[3];
		std::vector<Cell> cells_;
        std::vector<Cell> enterCells_;
		std::vector<std::shared_ptr<Vehicle>> vehicles_;
	};
}

