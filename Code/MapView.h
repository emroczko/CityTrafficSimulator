#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Simulator.h"
#include "Button.h"
#include "Definitions.h"
#include <vector>
#include "CreatorObserver.h"
#include "SimulationObserver.h"

namespace ZPR {
	class MapView : public CreatorObserver, public SimulationObserver
	{
	public:
		MapView(SimulatorDataRef data, int gridSize);
		void UpdateSelectedCell(sf::Vector2i coords);
		void UpdateCells(std::vector<Cell> cells);
        
		void UpdateIsDrawingRoad(bool isDrawingRoad);
        void UpdateIsDeletingRoad(bool isDeletingRoad);
        void UpdateIsSimulating(bool isSimulating);
		void UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles);
		void Draw();
		sf::Vector2i HandleInput(sf::Vector2f mousePosition);
		sf::View GetView();
		void init();
		sf::Vector2i getRowCol();
		bool isClicked(sf::Vector2i mousePosition);
		int getGridSize();
		int getCellSize();
        void zoomViewAt(sf::Vector2i pixel, float zoom);

	private:
        std::unique_ptr<Grid> _enterGrid;
        int _maximumZoom;
        bool clicked;
		void LoadAssets();
		sf::FloatRect CalculateViewPort();
		void DrawGrid();
        void DrawEnterGrid();
		void DrawRoads();
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
		void CheckRoadsTexture();
		void ChoseRoadWithOneNeighbour(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
			std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void ChoseRoadWithTwoNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
			std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
		void ChoseRoadWithThreeNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south,
			std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west);
        void DeleteRoad(sf::Vector2f position);
		bool CheckRoadExists(sf::Vector2f position);
		sf::Vector2f TransformRowColToPixels(sf::Vector2i rowcol);
		void setupSelectedCellRect();
		SimulatorDataRef _data;
		int _gridSize;
		int _cellSize;
		int _row, _col;
        int _enterGridHeight;
        int _enterGridWidth;
		bool isDrawingRoad;
        bool isDeletingRoad;
        bool isSimulating;
        sf::Vector2i _buffer;
		sf::RectangleShape _selectedCellRect;
		std::vector<sf::RectangleShape> _gridLines;
        std::vector<sf::RectangleShape> _enterGridLines;
		sf::Sprite _backgroundTexture;
		sf::View _mapView;
		std::vector<sf::RectangleShape> _roads;
		std::vector<Cell> _cells;
        std::vector<Cell> _enterCells;
		std::vector<std::shared_ptr<Vehicle>> _vehicles;

	};
}

