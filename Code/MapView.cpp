#include "MapView.h"
#include <iostream>

namespace ZPR {
	MapView::MapView(SimulatorDataRef data, int gridSize): _data(data), _gridSize(gridSize){
		init();
	}

	void MapView::init() {
		LoadAssets();
		setupSelectedCellRect();
		this->_backgroundTexture.setTexture(this->_data->assets.GetTexture("Background"));
		this->_cellSize = SCREEN_HEIGHT / this->_gridSize;
		this->_row = -1;
		this->_col = -1;
		this->_selectedCllRect.setTexture(&this->_data->assets.GetTexture("Selected Cell"));
		this->_mapView = sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_HEIGHT), (float)(SCREEN_HEIGHT)));
		this->_mapView.setViewport(CalculateViewPort());
		GenerateGridLines();
	}

	void MapView::LoadAssets()
	{
		this->_data->assets.LoadTexture("Selected Cell", SELECTED_CELL_TEXTURE);
		this->_data->assets.LoadTexture("Background", BACKGROUND_TEXTURE_FILEPATH);
	}

	void MapView::setupSelectedCellRect()
	{
		this->_selectedCllRect.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
		this->_selectedCllRect.setTexture(&this->_data->assets.GetTexture("Selected Cell"));
	}

	sf::FloatRect MapView::CalculateViewPort()
	{
		float rectWidth = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
		float rectLeft = (1.f - rectWidth)/2;
		return sf::FloatRect(rectLeft, 0.f, rectWidth, 1.f);
	}

	void MapView::DrawGrid() {
		for (sf::RectangleShape line : _gridLines) {
			this->_data->window.draw(line);
		}
	}

	void MapView::GenerateGridLines() {
		int drawPrefix = CalculatePrefix();
		for (int i = 0; i <= _gridSize; i++)
		{
			sf::RectangleShape verticalLine(sf::Vector2f(2, (_gridSize)*this->_cellSize));
			verticalLine.setPosition(sf::Vector2f(i * this->_cellSize + drawPrefix, drawPrefix));
			sf::RectangleShape horizontalLine(sf::Vector2f((_gridSize)*this->_cellSize, 2));
			horizontalLine.setPosition(sf::Vector2f(drawPrefix, i * this->_cellSize + drawPrefix));
			this->_gridLines.push_back(verticalLine);
			this->_gridLines.push_back(horizontalLine);
		}
	}

	int MapView::CalculatePrefix() {
		double cellSizeWithPoint = (double)SCREEN_HEIGHT / _gridSize;
		double theRest = cellSizeWithPoint - this->_cellSize;
		int drawPrefix = theRest * _gridSize / 2;
		return drawPrefix;
	}

	void MapView::fillCells()
	{
		int drawPrefix = CalculatePrefix();
		for (Cell cell : this->_cells) {
			int row = cell.GetPosition().x;
			int col = cell.GetPosition().y;
			if (row == this->_row && col == this->_col) {
				this->_selectedCllRect.setPosition(TransformRowColToPixels(sf::Vector2i(row, col)));
				this->_data->window.draw(this->_selectedCllRect);
			}
		}
	}

	sf::Vector2f MapView::TransformRowColToPixels(sf::Vector2i rowcol)
	{
		float x = rowcol.x * this->_cellSize + CalculatePrefix();
		float y = rowcol.y * this->_cellSize + CalculatePrefix();
		return sf::Vector2f(x, y);
	}

	void MapView::Draw()
	{
		this->_data->window.setView(this->_mapView);
		this->_data->window.draw(_backgroundTexture);
	    fillCells();
		DrawGrid();
	}


	void MapView::UpdateSelectedCell(sf::Vector2i coords)
	{
		int a = this->_cells.size();
		this->_row = coords.x;
		this->_col = coords.y;
	}

	void MapView::UpdateCells(std::vector<Cell> cells)
	{
		this->_cells = cells;
	}

	sf::Vector2i MapView::HandleInput(sf::Vector2f mousePosition)
	{
		int possibleSellectedRow= (int)(mousePosition.x / this->_cellSize);
		int possibleSellectedCol = (int)(mousePosition.y / this->_cellSize);
		return sf::Vector2i(possibleSellectedRow, possibleSellectedCol);
	}

	sf::View MapView::GetView()
	{
		return this->_mapView;
	}
}