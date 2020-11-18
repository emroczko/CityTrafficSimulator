#include "MapView.h"
#include <iostream>

namespace ZPR {
	MapView::MapView(SimulatorDataRef data, int gridSize): _data(data), _gridSize(gridSize){
		this->_data->assets.LoadTexture("Background", BACKGROUND_TEXTURE_FILEPATH);
		this->_backgroundTexture.setTexture(this->_data->assets.GetTexture("Background"));
		this->_data = data;
		this->_mapView = sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_HEIGHT), (float)(SCREEN_HEIGHT)));
		this->_mapView.setViewport(CalculateViewPort());
		GenerateGrid();
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

	void MapView::GenerateGrid() {
		double cellSizeWithPoint = _mapView.getSize().x / _gridSize;
		int cellSize = (int)cellSizeWithPoint;
		double theRest = cellSizeWithPoint - cellSize;
		int drawPrefix = theRest * _gridSize / 2;
		for (int i = 0; i <= _gridSize; i++)
		{
			sf::RectangleShape verticalLine(sf::Vector2f(2, (_gridSize)*cellSize));
			verticalLine.setPosition(sf::Vector2f(i * cellSize + drawPrefix, drawPrefix));
			sf::RectangleShape horizontalLine(sf::Vector2f((_gridSize)*cellSize, 2));
			horizontalLine.setPosition(sf::Vector2f(drawPrefix, i * cellSize + drawPrefix));
			this->_gridLines.push_back(verticalLine);
			this->_gridLines.push_back(horizontalLine);
		}
	}

	void MapView::Draw()
	{
		this->_data->window.setView(this->_mapView);
		this->_data->window.draw(_backgroundTexture);
		DrawGrid();
	}
}