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
		virtual void UpdateCells(std::vector<Cell> cells);
		void Draw();
		sf::Vector2i HandleInput(sf::Vector2f mousePosition);
		sf::View GetView();
		void init();
		sf::Vector2i getRowCol();
		int getGridSize();
		int getCellSize();
	private:
		void LoadAssets();
		sf::FloatRect CalculateViewPort();
		void DrawGrid();
		void GenerateGridLines();
		int CalculatePrefix();
		void fillCells();
		sf::Vector2f TransformRowColToPixels(sf::Vector2i rowcol);
		void setupSelectedCellRect();
		SimulatorDataRef _data;
		int _gridSize;
		int _cellSize;
		int _row, _col;
		sf::RectangleShape _selectedCllRect;
		std::vector<sf::RectangleShape> _gridLines;
		sf::Sprite _backgroundTexture;
		sf::View _mapView;
		std::vector<Cell> _cells;
	};
}

