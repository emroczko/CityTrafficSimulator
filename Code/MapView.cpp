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
		this->_selectedCellRect.setTexture(&this->_data->assets.GetTexture("Selected Cell"));
		this->_mapView = sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_HEIGHT), (float)(SCREEN_HEIGHT)));
		this->_mapView.setViewport(CalculateViewPort());
		GenerateGridLines();
        _buffer = sf::Vector2i(0,0);
	}

	sf::Vector2i MapView::getRowCol()
	{
		return sf::Vector2i(this->_row, this->_col);
	}

	int MapView::getGridSize()
	{
		return this->_gridSize;
	}

	int MapView::getCellSize()
	{
		return this->_cellSize;
	}

	bool MapView::isClicked(sf::Vector2i& mousePosition)
	{
		if (_mapView.getViewport().contains(static_cast<float>(mousePosition.x) / SCREEN_WIDTH, static_cast<float>(mousePosition.y) / SCREEN_HEIGHT))
			return true;
		else
			return false;
	}
    bool MapView::isReleased(sf::Vector2i& mousePosition)
    {
        fillCells();
        if (_mapView.getViewport().contains(static_cast<float>(mousePosition.x) / SCREEN_WIDTH, static_cast<float>(mousePosition.y) / SCREEN_HEIGHT)){
            if (_tempRoad.size() == 1){
                _tempRoad[0].setTexture(NULL);
                _tempRoad.clear();
            }
            _roads.insert(_roads.end(), _tempRoad.begin(), _tempRoad.end());
            _tempRoad.clear();
            return true;
        }
        else{
            return false;
        }
    }

	/*Wczytuje wszystkie potrzebne assety*/
	void MapView::LoadAssets()
	{
		this->_data->assets.LoadTexture("Selected Cell", SELECTED_CELL_TEXTURE);
		this->_data->assets.LoadTexture("Background", BACKGROUND_TEXTURE_FILEPATH);
		this->_data->assets.LoadTexture("Road", STREET_TEXTURE);
		this->_data->assets.LoadTexture("Turn", TURN_TEXTURE);
		this->_data->assets.LoadTexture("T_Intersection", T_INTERSECTION_TEXTURE);
		this->_data->assets.LoadTexture("Intersection", INTERSECTION_TEXTURE);
		this->_data->assets.LoadTexture("Crossing", CROSSING_TEXTURE);
	}

	void MapView::setupSelectedCellRect()
	{
		this->_selectedCellRect.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
		this->_selectedCellRect.setTexture(&this->_data->assets.GetTexture("Selected Cell"));
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

	void MapView::DrawRoads(){
		for (sf::RectangleShape road : this->_roads) {
			this->_data->window.draw(road);
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

		for (Cell& cell : this->_cells) {
			int row = cell.GetPosition().x;
			int col = cell.GetPosition().y;
			if (cell._containsRoad && !cell._roadDrawn) {
				cell._roadDrawn = true;
				AddRoad(sf::Vector2i(row, col));
                //CellBuffer(sf::Vector2i(row, col), cell);
			}
            if (cell._toDelete) {
                DeleteRoad(TransformRowColToPixels(sf::Vector2i(row, col)));
            }
			if (row == this->_row && col == this->_col) {
				this->_selectedCellRect.setPosition(TransformRowColToPixels(sf::Vector2i(row, col)));
				this->_data->window.draw(this->_selectedCellRect);
			}
		}
        
        
	}

	/*Dodaje drogê*/
	void MapView::AddRoad(sf::Vector2i position)
	{
		if (CheckRoadExists(TransformRowColToPixels(sf::Vector2i(position.x, position.y)))) { return; }
		sf::RectangleShape road;
		road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
		road.setTexture(&this->_data->assets.GetTexture("Road"));
		road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
		sf::Vector2f centeredPositionInPixels = TransformRowColToPixels(sf::Vector2i(position.x, position.y));
		centeredPositionInPixels.x = centeredPositionInPixels.x + this->_cellSize / 2;
		centeredPositionInPixels.y = centeredPositionInPixels.y + this->_cellSize / 2;
		road.setPosition(centeredPositionInPixels);
		this->_roads.push_back(road);
		CheckWhichRoadToAdd(position);
	}

    void MapView::CellBuffer(sf::Vector2i position, Cell &cell){
        int x, y;
        x = position.x - _buffer.x;
        y = position.y - _buffer.y;
        
        if (x > 0){
            cell._east = true;
        }
        else if(x < 0){
            cell._west = true;
        }
        else {
            cell._east = false;
            cell._west = false;
        }
        
        if (y > 0){
            cell._south = true;
        }
        else if(x < 0){
            cell._north = true;
        }
        else {
            cell._north = false;
            cell._south = false;
        }
        _buffer.x = position.x;
        _buffer.y = position.y;
    }

	
	void MapView::CheckWhichRoadToAdd(sf::Vector2i position) {
		for (sf::RectangleShape& road : this->_roads) {
			std::shared_ptr<sf::RectangleShape> north = nullptr;
			std::shared_ptr<sf::RectangleShape> south = nullptr;
			std::shared_ptr<sf::RectangleShape> east = nullptr;
			std::shared_ptr<sf::RectangleShape> west = nullptr;
			int row = road.getPosition().y / this->_cellSize;
			int col = road.getPosition().x / this->_cellSize;
			if (row >= this->_row - 1 && row <= this->_row + 1 && col >= this->_col - 1 && col <= this->_col + 1) {
				for (sf::RectangleShape& neighbouring_road : this->_roads) {
					int neighbouring_row = neighbouring_road.getPosition().y / this->_cellSize;
					int neighbouring_col = neighbouring_road.getPosition().x / this->_cellSize;
					if (row == neighbouring_row) {
						if (col + 1 == neighbouring_col) { east = std::make_shared<sf::RectangleShape>(neighbouring_road); }
						if (col - 1 == neighbouring_col) { west = std::make_shared<sf::RectangleShape>(neighbouring_road); }
					}
					if (col == neighbouring_col) {
						if (row + 1 == neighbouring_row) { south = std::make_shared<sf::RectangleShape>(neighbouring_road); }
						if (row - 1 == neighbouring_row) { north = std::make_shared<sf::RectangleShape>(neighbouring_road); }
					}
				}
				road.setTexture(&this->_data->assets.GetTexture("Road"));
				if (north)
				{
					if (east)
					{
						road.setTexture(&this->_data->assets.GetTexture("Turn"));
					}
					else if (west)
					{
						road.setTexture(&this->_data->assets.GetTexture("Turn"));
						road.rotate(90.f);
					}
					else if (west && east) {
						road.setTexture(&this->_data->assets.GetTexture("T_Intersection"));
						road.rotate(90.f);
					}
					else {
						road.setTexture(&this->_data->assets.GetTexture("Road"));
						road.rotate(90.f);
					}
				}
				if (east)
				{
					if (south)
					{
						road.setTexture(&this->_data->assets.GetTexture("Turn"));
						road.rotate(270.f);
					}
					else if (south && north) {
						road.setTexture(&this->_data->assets.GetTexture("T_Intersection"));
					}
					else {
						road.setTexture(&this->_data->assets.GetTexture("Road"));
					}
				}
				if (south)
				{
					if (west)
					{
						road.setTexture(&this->_data->assets.GetTexture("Turn"));
						road.rotate(180.f);
					}
					else if (west && east) {
						road.setTexture(&this->_data->assets.GetTexture("T_Intersection"));
						road.rotate(270.f);
					}
					else {
						road.setTexture(&this->_data->assets.GetTexture("Road"));
						road.setRotation(90.f);
					}
				}
				if (west)
				{
					if (south && north)
					{
						road.setTexture(&this->_data->assets.GetTexture("T_Intersection"));
						road.rotate(180.f);
					}
				}
				if (north && south && east && west) {
					road.setTexture(&this->_data->assets.GetTexture("Intersection"));
				}
			}
		}
	}

	
	


    void MapView::DeleteRoad(sf::Vector2f position)
    {
		int i = 0;
		if (CheckRoadExists(TransformRowColToPixels(sf::Vector2i(position.x, position.y)))) { return; }
        
		for (sf::RectangleShape road : _roads) {
			if (road.getPosition() == position){
				_roads.erase(_roads.begin() + i);
				road.setTexture(NULL);
			}
			i++;
		}
	}
	/*Sprawdza czy droga na podanej pozycji istnieje*/
	bool MapView::CheckRoadExists(sf::Vector2f position) {
		for (sf::RectangleShape road : this->_roads) {
			if (road.getPosition() == position) {return true;}
		}
		return false;
	}

	/*Zmiania koordynaty wiarsz-kolumna z siatki na koordynaty w pixelach*/
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
		DrawRoads();
		
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

	void MapView::UpdateIsDrawingRoad(bool isDrawingRoad)
	{
		this->isDrawingRoad = isDrawingRoad;
        this->isDeletingRoad = false;
	}

    void MapView::UpdateIsDeletingRoad(bool isDeletingRoad)
    {
        this->isDeletingRoad = isDeletingRoad;
        this->isDrawingRoad = false;
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
