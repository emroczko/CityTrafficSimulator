#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Simulator.h"
#include "Button.h"
#include "Definitions.h"
#include <vector>
#include "CreatorObserver.h"
#include "SimulationObserver.h"
#include "SimulationHandler.h"
#include "KeysEnum.h"


namespace ZPR {
	class MapView : public CreatorObserver, public SimulationObserver
	{
	public:
		MapView(SimulatorDataRef data, int gridSize);
        MapView(const MapView& mapView);
		void UpdateSelectedCell(sf::Vector2i coords);
		void UpdateCells(std::vector<Cell> cells);
        void UpdateRoads(std::vector<sf::RectangleShape> roads);
		void UpdateIsDrawingRoad(bool isDrawingRoad);
        void UpdateIsDeletingRoad(bool isDeletingRoad);
        void UpdateIsSimulating(bool isSimulating);
        void UpdateIsAddingCamera(bool isAddingCamera, int whichCamera);
        void UpdateIsDeletingCamera(int whichCamera);
        void SaveToFile();
		void UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles);
		void Draw();
		sf::Vector2i HandleInput(sf::Vector2f mousePosition);
		sf::View GetView();
		void init();
		sf::Vector2i getRowCol();
		bool isClicked(sf::Vector2i mousePosition);
        void Move(keysEnum key);
		int getGridSize();
		int getCellSize();
        std::vector<Cell> GetCells();
        void zoomViewAt(sf::Vector2f pixel, float zoom);
        friend std::ofstream& operator<< (std::ofstream& ,const MapView&);
        friend std::ostream& operator<< (std::ostream& ,const MapView&);
	private:
        void InitializeCameras();
        std::unique_ptr<Grid> _enterGrid;
        int _maximumZoom;
        bool clicked;
		void LoadAssets();
		sf::FloatRect CalculateViewPort();
		void DrawGrid();
        void DrawEnterGrid();
		void DrawRoads();
        void DrawEntryRoads();
		void DrawVehicles();
        void DrawCameras();
		void GenerateGridLines();
        void GenerateEnterGridLines();
        void GenerateEnterBoard();
		int CalculatePrefix();
		void FillCells();
        void FillEnterCells();
        void AddRoad(std::string fileName, sf::Vector2i position);
		void AddUserRoad(sf::Vector2i position);
        void AddGarage(sf::Vector2i position);
        void AddEnterRoad(sf::Vector2i position);
        void AddCamera(sf::Vector2i position);
		void CheckRoadsTexture();
		void ChoseRoadWithOneNeighbour(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
			std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west, int row, int col);
		void ChoseRoadWithTwoNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
			std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void ChoseRoadWithThreeNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
			std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
        void DeleteRoad(sf::Vector2f position);
        void DeleteCamera(sf::Vector2f position);
		bool CheckRoadExists(sf::Vector2f position);
        bool CheckCameraExists(sf::Vector2f position);
		sf::Vector2f TransformRowColToPixels(sf::Vector2i rowcol);
        int TransformPixelsToRowCol(double pixels);
		void setupSelectedCellRect();
		SimulatorDataRef _data;
		int _gridSize;
		int _cellSize;
        int _whichCamera;
		int _row, _col;
        int _enterGridHeight;
        int _enterGridWidth;
		bool isDrawingRoad;
        bool isDeletingRoad;
        bool isSimulating;
        bool isAddingCamera;
        sf::Vector2i _buffer;
		sf::RectangleShape _selectedCellRect;
		std::vector<sf::RectangleShape> _gridLines;
        std::vector<sf::RectangleShape> _enterGridLines;
		sf::Sprite _backgroundTexture;
		sf::View _mapView;
        std::vector<sf::RectangleShape> _roads, _entryRoad, _cameras;
        sf::RectangleShape _camerasT[3];
		std::vector<Cell> _cells;
        std::vector<Cell> _enterCells;
		std::vector<std::shared_ptr<Vehicle>> _vehicles;
        
        
	};
}

