#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Simulator.h"
#include "Button.h"
#include "Definitions.h"
#include <vector>
#include "CreatorObserver.h"

namespace ZPR {
	class MapView : public CreatorObserver
	{
	public:
		MapView(SimulatorDataRef data, int gridSize);
		void UpdateSelectedCell(sf::Vector2i coords);
		void UpdateCells(std::vector<Cell> cells);
		void UpdateIsDrawingRoad(bool isDrawingRoad);
        void UpdateIsDeletingRoad(bool isDeletingRoad);
		void Draw();
		sf::Vector2i HandleInput(sf::Vector2f mousePosition);
		sf::View GetView();
		void init();
		sf::Vector2i getRowCol();
		int getGridSize();
		int getCellSize();
		bool isClicked(sf::Vector2i &mousePosition);
	private:
		void LoadAssets();
		sf::FloatRect CalculateViewPort();
		void DrawGrid();
		void DrawRoads();
		void GenerateGridLines();
		int CalculatePrefix();
		void fillCells();
		void CheckWhichRoadToAdd(sf::Vector2i position);
		void AddRoad(sf::Vector2i position);
        void DeleteRoad(sf::Vector2f position);
		bool CheckRoadExists(sf::Vector2f position);
		sf::Vector2f TransformRowColToPixels(sf::Vector2i rowcol);
		void setupSelectedCellRect();
		SimulatorDataRef _data;
		int _gridSize;
		int _cellSize;
		int _row, _col;
		bool isDrawingRoad;
        bool isDeletingRoad;
		sf::RectangleShape _selectedCellRect;
		std::vector<sf::RectangleShape> _gridLines;
		sf::Sprite _backgroundTexture;
		sf::View _mapView;
		std::vector<sf::RectangleShape> _roads;
		std::vector<Cell> _cells;
	};
}

