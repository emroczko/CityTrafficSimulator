#include "MapView.h"
#include <iostream>

namespace ZPR {
	MapView::MapView(SimulatorDataRef data, int gridSize): _data(data), _gridSize(gridSize){
		init();
	}

	void MapView::init() {
        this->clicked = false;
		LoadAssets();
		setupSelectedCellRect();
		this->_backgroundTexture.setTexture(this->_data->assets.GetTexture("Background"));
		this->_backgroundTexture.setOrigin(sf::Vector2f(800, 800));
		this->_backgroundTexture.setPosition(this->_mapView.getCenter());
		this->_cellSize = (SCREEN_HEIGHT / this->_gridSize);
		this->_row = -1;
		this->_col = -1;
        this->_enterGridWidth = this->_gridSize;
        this->_enterGridHeight = 2;
		this->_selectedCellRect.setTexture(&this->_data->assets.GetTexture("Selected Cell"));
		this->_mapView = sf::View(sf::FloatRect(0.f, 0.f, (float)(SCREEN_HEIGHT), (float)(SCREEN_HEIGHT)));
		this->_mapView.setViewport(CalculateViewPort());
		GenerateGridLines();
        //GenerateEnterGridLines();
        GenerateEnterBoard();
        this->_mapView.zoom(1.4f);
        FillEnterCells();
        
	}
	/*Zwraca wartoœci kolumny i wiersza obecnie zaznaczonej komórki*/
	sf::Vector2i MapView::getRowCol()
	{
		return sf::Vector2i(this->_row, this->_col);
	}
	/*Sprawdza czy klikniete miejsce w oknie programu jest wewn¹trz segmentu mapy*/
	bool MapView::isClicked(sf::Vector2i mousePosition)
	{
		if (_mapView.getViewport().contains(static_cast<float>(mousePosition.x) / SCREEN_WIDTH, static_cast<float>(mousePosition.y) / SCREEN_HEIGHT)) {
			clicked = true;
			return true;
		}
		else
			return false;
	}

	int MapView::getGridSize()
	{
		return this->_gridSize;
	}

	int MapView::getCellSize()
	{
		return this->_cellSize;
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
        this->_data->assets.LoadTexture("Entry", ENTRY_TEXTURE);
	}
	/*Ustawia podstawowe parametry kwadratu reprezentuj¹cego zaznaczone pole na mapie*/
	void MapView::setupSelectedCellRect()
	{
		this->_selectedCellRect.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
		this->_selectedCellRect.setTexture(&this->_data->assets.GetTexture("Selected Cell"));
	}
	/*Oblicza po³o¿enie obiektu typu sf::View*/
	sf::FloatRect MapView::CalculateViewPort()
	{
        float rectWidth = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
		float rectLeft = (1.f - rectWidth)/2;
		return sf::FloatRect(rectLeft, 0.f, rectWidth, 1.f);
	}
    void MapView::GenerateEnterBoard()
    {
        std::vector<Cell> enterCells;
        for (int i = 0; i < this->_enterGridHeight * this->_gridSize; i++)
        {
            enterCells.push_back(Cell( i % _gridSize, (-i / _gridSize)-1));
        }
        this->_enterGrid = std::make_unique<Grid>(enterCells, _gridSize, _enterGridHeight);
        this->_enterCells = _enterGrid->_cells;
    }
	/*Rysuje siatke na mapie*/
	void MapView::DrawGrid() {
        if(!isSimulating){
            for (sf::RectangleShape line : _gridLines) {
                this->_data->window.draw(line);
            }
        }
	}
    void MapView::DrawEnterGrid() {
            for (sf::RectangleShape line : _enterGridLines) {
                this->_data->window.draw(line);
            }
    }
	/*Rysuje wszystkie drogi*/
	void MapView::DrawRoads(){
		for (sf::RectangleShape road : this->_roads) {
			this->_data->window.draw(road);
		}
	}
	/*Tworzy linie reprezentuj¹ce siatkê na mapie*/
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
    void MapView::GenerateEnterGridLines() {
        int drawPrefix = CalculatePrefix();
        for (int i = 0; i <= _enterGridWidth; i++)
        {
            sf::RectangleShape verticalLine(sf::Vector2f(2, (_enterGridHeight)*this->_cellSize));
            verticalLine.setPosition(sf::Vector2f(i * this->_cellSize + drawPrefix, drawPrefix- 2*this->_cellSize));
            
            this->_enterGridLines.push_back(verticalLine);
            
        }
        for (int i = 1; i <= _enterGridHeight; i++){
            
            sf::RectangleShape horizontalLine(sf::Vector2f((_enterGridWidth)*this->_cellSize, 2));
            horizontalLine.setPosition(sf::Vector2f(drawPrefix, -i * this->_cellSize + drawPrefix));
            this->_enterGridLines.push_back(horizontalLine);
        }
    }

	int MapView::CalculatePrefix() {
		double cellSizeWithPoint = (double)SCREEN_HEIGHT / _gridSize;
		double theRest = cellSizeWithPoint - this->_cellSize;
		int drawPrefix = theRest * _gridSize / 2;
		return drawPrefix;
	}

	/*Zajmuje siê wype³nianiem komórek w odpowiedni sposób (dodawanie do niej drogi lub usuwanie drogi)*/
	void MapView::FillCells()
	{
		for (Cell& cell : this->_cells) {
			int row = cell.GetPosition().x;
			int col = cell.GetPosition().y;
			if (cell._containsRoad && !cell._roadDrawn) {
				cell._roadDrawn = true;
				AddUserRoad(sf::Vector2i(row, col));
			}
            if (cell._toDelete) {
                DeleteRoad(TransformRowColToPixels(sf::Vector2i(row, col)));
				cell._toDelete = false;
            }
			
		}
	}
    void MapView::FillEnterCells()
    {
        for (Cell& cell : this->_enterCells) {
            int col = cell.GetPosition().x;
            int row = cell.GetPosition().y;
            if(row == -2)
                AddEnterRoad(sf::Vector2i(col, row));
            else if(row == -1 && col == 4)
                AddEnterRoad(sf::Vector2i(col, row));
    }
        AddGarage(sf::Vector2i(0, -2));
        AddGarage(sf::Vector2i(15, -2));
}

    void MapView::AddRoad(std::string fileName, sf::Vector2i position){
        sf::RectangleShape road;
        road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
        road.setTexture(&this->_data->assets.GetTexture(fileName));
        road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
        sf::Vector2f centeredPositionInPixels = TransformRowColToPixels(sf::Vector2i(position.x, position.y));
        centeredPositionInPixels.x = centeredPositionInPixels.x + this->_cellSize / 2 ;
        centeredPositionInPixels.y = centeredPositionInPixels.y + this->_cellSize / 2 ;
        road.setPosition(centeredPositionInPixels);
        std::cout <<road.getPosition().x << "   " <<road.getPosition().y<< std::endl;;
        this->_roads.push_back(road);
    }
	/*Dodaje drogê*/
	void MapView::AddUserRoad(sf::Vector2i position)
	{
		if (CheckRoadExists(TransformRowColToPixels(sf::Vector2i(position.x, position.y)))) { return; }
        AddRoad("Road", position);
		CheckRoadsTexture();
	}
    void MapView::AddEnterRoad(sf::Vector2i position){
        AddRoad("Road", position);
        CheckRoadsTexture();
    }
    void MapView::AddGarage(sf::Vector2i position){
        AddRoad("Entry", position);
    }
	/*Sprawdza czy drogi maja ustawione odpowiednia textury tak aby rysowana droga wyg¹da³a na ci¹g³¹ i spujn¹*/
	void MapView::CheckRoadsTexture() {
		for (sf::RectangleShape& road : this->_roads) {
			std::shared_ptr<sf::RectangleShape> north = nullptr;
			std::shared_ptr<sf::RectangleShape> south = nullptr;
			std::shared_ptr<sf::RectangleShape> east = nullptr;
			std::shared_ptr<sf::RectangleShape> west = nullptr;
			std::vector<std::shared_ptr<sf::RectangleShape>> neighbouringRoadsPtr;
			int row = road.getPosition().y / this->_cellSize;
			int col = road.getPosition().x / this->_cellSize;
			for (sf::RectangleShape& neighbouringRoad : this->_roads) {
				int neighbouring_row = neighbouringRoad.getPosition().y / this->_cellSize;
				int neighbouring_col = neighbouringRoad.getPosition().x / this->_cellSize;
				if (row == neighbouring_row) {
					if (col + 1 == neighbouring_col) {
						east = std::make_shared<sf::RectangleShape>(neighbouringRoad);
						neighbouringRoadsPtr.push_back(east);
					}
					if (col - 1 == neighbouring_col) {
						west = std::make_shared<sf::RectangleShape>(neighbouringRoad);
						neighbouringRoadsPtr.push_back(west);
					}
				}
				if (col == neighbouring_col) {
					if (row + 1 == neighbouring_row) {
						south = std::make_shared<sf::RectangleShape>(neighbouringRoad);
						neighbouringRoadsPtr.push_back(south);
					}
					if (row - 1 == neighbouring_row) {
						north = std::make_shared<sf::RectangleShape>(neighbouringRoad);
						neighbouringRoadsPtr.push_back(north);
					}
				}
			}
			switch (neighbouringRoadsPtr.size()) {
			case 0: road.setTexture(&this->_data->assets.GetTexture("Road")); break;
			case 1: ChoseRoadWithOneNeighbour(road, north, south, east, west); break;
			case 2: ChoseRoadWithTwoNeighbours(road, north, south, east, west); break;
			case 3: ChoseRoadWithThreeNeighbours(road, north, south, east, west); break;
			case 4: road.setTexture(&this->_data->assets.GetTexture("Intersection")); break;
			}
		}
	}

	/*Ustawia drodze odpowiedni¹ teksturê w przypadku w którym droga ma tylko jedn¹ s¹siaduj¹c¹ drogê*/
	void MapView::ChoseRoadWithOneNeighbour(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
	{
		road.setTexture(&this->_data->assets.GetTexture("Road"));
		road.setRotation(0);
		if (north) {
			road.setRotation(90.f);
		}
		else if (south) {
			road.setRotation(90.f);
		}
	}
	/*Ustawia drodze odpowiedni¹ teksturê w przypadku w którym droga ma dwie s¹siaduj¹ce drogi*/
	void MapView::ChoseRoadWithTwoNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
	{
		road.setTexture(&this->_data->assets.GetTexture("Turn"));
		
		if (north && east) { road.setRotation(0); }
		else if (north && west) {
			road.setRotation(270.f);
		}
		else if (south && east) {
			road.setRotation(90.f);
		}
		else if (south && west) {
			road.setRotation(180.f);
		}
		else if (north && south) {
			road.setTexture(&this->_data->assets.GetTexture("Road"));
			road.setRotation(90.f);
		}
		else if (east && west) {
			road.setTexture(&this->_data->assets.GetTexture("Road"));
			road.setRotation(0);
		}
	}
	/*Ustawia drodze odpowiedni¹ teksturê w przypadku w którym droga ma trzy s¹siaduj¹ce drogi*/
	void MapView::ChoseRoadWithThreeNeighbours(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west)
	{
		road.setTexture(&this->_data->assets.GetTexture("T_Intersection"));
		if (north && south && east) { road.setRotation(0.f); }
		else if (north && south && west) {
			road.setRotation(180.f);
		}
		else if (north && east && west) {
			road.setRotation(270.f);
		}
		else if (south && east && west) {
			road.setRotation(90.f);
		}
	}
	/*Usuwa drogê z mapy*/
    void MapView::DeleteRoad(sf::Vector2f position)
    {
		int i = 0;
		if (CheckRoadExists(TransformRowColToPixels(sf::Vector2i(position.x, position.y)))) { return; }
        
		for (sf::RectangleShape road : _roads) {
			if (road.getPosition().x - this->_cellSize / 2 == position.x && road.getPosition().y - this->_cellSize / 2 == position.y){
				_roads.erase(_roads.begin() + i);
				road.setTexture(NULL);
			}
			i++;
		}
		CheckRoadsTexture();
	}
	/*Sprawdza czy droga na podanej pozycji istnieje*/
	bool MapView::CheckRoadExists(sf::Vector2f position) {
		for (sf::RectangleShape road : this->_roads) {
			if (road.getPosition().x -this->_cellSize/2 == position.x && road.getPosition().y - this->_cellSize/2 == position.y) {return true;}
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
	/*Rysuje wszystkie elementy mapy*/
	void MapView::Draw()
	{
		this->_data->window.setView(this->_mapView);
		this->_data->window.draw(_backgroundTexture);
		FillCells();
        
		DrawRoads();
		DrawGrid();
        //DrawEnterGrid();
	}

    void MapView::zoomViewAt(sf::Vector2i pixel, float zoom)
    {
        //const sf::Vector2f beforeCoord{_data->window.mapPixelToCoords(pixel) };
        //sf::View view{ window.getView() };
        
        if (zoom < 0){
            this->_mapView.zoom(1.f/zoom);
             
        }
        else{
            this->_mapView.zoom(zoom);
        }
        _data->window.setView(_mapView);
        //const sf::Vector2f afterCoord{ _data->window.mapPixelToCoords(pixel) };
       // const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
        //_mapView.move(offsetCoords);
        //_data->window.setView(_mapView);
    }
    


	/*Odœwierza wartosæ koordynatów obecnie klikniêtego pola*/

	void MapView::UpdateSelectedCell(sf::Vector2i coords)
	{
		int a = this->_cells.size();
		this->_row = coords.x;
		this->_col = coords.y;
	}
	/*Odswierza wszystkie komórki znajduj¹ce siê na mapie*/
	void MapView::UpdateCells(std::vector<Cell> cells)
	{
		this->_cells = cells;
	}
    
	/*Odœwierza wartosc zminnej decyduj¹cej o tym czy jestesmy w trybie rysowania drogi*/
	void MapView::UpdateIsDrawingRoad(bool isDrawingRoad)
	{
		this->isDrawingRoad = isDrawingRoad;
        this->isDeletingRoad = false;
        this->isSimulating = false;
	}

    void MapView::UpdateIsDeletingRoad(bool isDeletingRoad)
    {
        this->isDeletingRoad = isDeletingRoad;
        this->isDrawingRoad = false;
        this->isSimulating = false;
    }
    void MapView::UpdateIsSimulating(bool isSimulating){
        this->isSimulating = isSimulating;
        this->isDrawingRoad = false;
        this->isDeletingRoad = false;
    }

	void MapView::UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles)
	{
		this->_vehicles = vehicles;
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
