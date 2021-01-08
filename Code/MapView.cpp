#include "MapView.h"
#include <random>


namespace ZPR {
	MapView::MapView(SimulatorDataRef data, int gridSize): _data(data), _gridSize(gridSize){
		init();
	}
    
    MapView::MapView(const MapView& mapView): _data(mapView._data), _gridSize(mapView._gridSize), _cells(mapView._cells){
    }
	/*Inicjuje wyszystkie elementy potrzebne do poprawnego dzia≥ania mapy*/
	void MapView::init() {
        this->clicked = false;
		LoadAssets();
		setupSelectedCellRect();
        this->_whichCamera = 0;
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
        GenerateEnterBoard();
        this->_mapView.zoom(1.4f);
        this->InitializeCameras();
        FillEnterCells();
	}
    void MapView::InitializeCameras(){
        sf::RectangleShape temp;
        for(int i = 0; i < 2; i++){
            _cameras.push_back(temp);
        }
    }
	/*Zwraca wartoúci kolumny i wiersza obecnie zaznaczonej komÛrki*/
	sf::Vector2i MapView::getRowCol()
	{
		return sf::Vector2i(this->_row, this->_col);
	}
	/*Sprawdza czy klikniete miejsce w oknie programu jest wewnπtrz segmentu mapy*/
	bool MapView::isClicked(sf::Vector2i mousePosition)
	{
		if (_mapView.getViewport().contains(static_cast<float>(mousePosition.x) / SCREEN_WIDTH, static_cast<float>(mousePosition.y) / SCREEN_HEIGHT)) {
			clicked = true;
			return true;
		}
		else
			return false;
	}
	/*Zwraca rozmiar siatki mapy*/
	int MapView::getGridSize()
	{
		return this->_gridSize;
	}
	/*Zwraca rozmiar pojedyÒczej komÛrki w pikselach */
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
        this->_data->assets.LoadTexture("Camera", CAMERA_TEXTURE);
	}
	/*Ustawia podstawowe parametry kwadratu reprezentujπcego zaznaczone pole na mapie*/
	void MapView::setupSelectedCellRect()
	{
		this->_selectedCellRect.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
		this->_selectedCellRect.setTexture(&this->_data->assets.GetTexture("Selected Cell"));
	}
	/*Oblicza po≥oøenie obiektu typu sf::View*/
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
            enterCells.push_back(Cell(((i / _gridSize)-2), i % _gridSize));
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
	/*Rysuje wszystkie drogi*/
	void MapView::DrawRoads(){
		for (sf::RectangleShape road : this->_roads) {
			this->_data->window.draw(road);
		}
	}
    void MapView::DrawEntryRoads(){
        for (sf::RectangleShape road : this->_entryRoad) {
            this->_data->window.draw(road);
        }
    }
	void MapView::DrawVehicles()
	{
		for (std::shared_ptr<Vehicle> vehicle : this->_vehicles) {
			this->_data->window.draw(*vehicle);
		}
	}
    void MapView::DrawCameras(){
        for (sf::RectangleShape camera : this->_cameras) {
            this->_data->window.draw(camera);
        }
    }
    
	/*Tworzy linie reprezentujπce siatkÍ na mapie*/
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
	/*Oblicza iloúÊ pixeli o jakπ musimy przesunπÊ siatkÍ aby by≥a ona wyúrodkowana*/
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
	/*Zajmuje siÍ wype≥nianiem komÛrek w odpowiedni sposÛb (dodawanie do niej drogi lub usuwanie drogi)*/
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
            if (cell._containsCamera && !cell._cameraDrawn) {
                cell._cameraDrawn = true;
                AddCamera((sf::Vector2i(row, col)));
            }
            if (cell._cameraToDelete) {
                DeleteCamera(TransformRowColToPixels(sf::Vector2i(row, col)));
                cell._cameraToDelete = false;
            }
		}
	}
    void MapView::FillEnterCells()
    {
        
        for (Cell& cell : this->_enterCells) {
            int row = cell.GetPosition().x;
            int col = cell.GetPosition().y;
            if(row == -2 && col != 0 && col != _gridSize-1){
                AddEnterRoad(sf::Vector2i(col, row));
            }
            else if(row == -1 && col == 4){
                AddEnterRoad(sf::Vector2i(col, row));
            }
            
		}
        AddGarage(sf::Vector2i(0, -2));
        AddGarage(sf::Vector2i(_gridSize-1, -2));
	}

	/*Dodaje drogÍ*/
    void MapView::AddRoad(std::string fileName, sf::Vector2i position){
        sf::RectangleShape road;
        road.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
        road.setTexture(&this->_data->assets.GetTexture(fileName));
        road.setOrigin(sf::Vector2f(road.getSize().x / 2, road.getSize().y / 2));
        sf::Vector2f centeredPositionInPixels = TransformRowColToPixels(sf::Vector2i(position.x, position.y));
        centeredPositionInPixels.x = centeredPositionInPixels.x + this->_cellSize / 2 ;
        centeredPositionInPixels.y = centeredPositionInPixels.y + this->_cellSize / 2 ;
        road.setPosition(centeredPositionInPixels);
        this->_roads.push_back(road);
    }
    void MapView::AddCamera(sf::Vector2i position){
        sf::RectangleShape camera;
        camera.setSize(sf::Vector2f(SCREEN_HEIGHT / this->_gridSize, SCREEN_HEIGHT / this->_gridSize));
        camera.setTexture(&this->_data->assets.GetTexture("Camera"));
        camera.setOrigin(sf::Vector2f(camera.getSize().x / 2, camera.getSize().y / 2));
        sf::Vector2f centeredPositionInPixels = TransformRowColToPixels(sf::Vector2i(position.x, position.y));
        centeredPositionInPixels.x = centeredPositionInPixels.x + this->_cellSize / 2 ;
        centeredPositionInPixels.y = centeredPositionInPixels.y + this->_cellSize / 2 ;
        camera.setPosition(centeredPositionInPixels);
        //int cam = _whichCamera;
        auto itPos = _cameras.begin() + _whichCamera;
        this->_cameras.insert(itPos, camera);
        //emplace(_cameras.begin()+_whichCamera, camera);
    }
    
    void MapView::AddEnterRoad(sf::Vector2i position){
        AddRoad("Road", position);
        CheckRoadsTexture();
    }
    void MapView::AddGarage(sf::Vector2i position){
        AddRoad("Entry", position);
    }

    /*Dodaje drogê*/
    void MapView::AddUserRoad(sf::Vector2i position)
    {
        if (CheckRoadExists(TransformRowColToPixels(sf::Vector2i(position.x, position.y)))) { return; }
        AddRoad("Road", position);
        CheckRoadsTexture();
    }
    int MapView::TransformPixelsToRowCol(double pixels){
        int result;
        
        if(pixels < 0){
            result = floor(pixels / this->_cellSize);
        }else{
            result = pixels / this->_cellSize;
        }
        return result;
    }
	/*Sprawdza czy drogi maja ustawione odpowiednia textury tak aby rysowana droga wygπda≥a na ciπg≥π i spujnπ*/
	void MapView::CheckRoadsTexture() {
		for (sf::RectangleShape& road : this->_roads) {
			std::shared_ptr<sf::RectangleShape> north = nullptr;
			std::shared_ptr<sf::RectangleShape> south = nullptr;
			std::shared_ptr<sf::RectangleShape> east = nullptr;
			std::shared_ptr<sf::RectangleShape> west = nullptr;
			std::vector<std::shared_ptr<sf::RectangleShape>> neighbouringRoadsPtr;
            int row = TransformPixelsToRowCol(road.getPosition().y);
            int col = TransformPixelsToRowCol(road.getPosition().x);
			for (sf::RectangleShape& neighbouringRoad : this->_roads) {
                int neighbouring_row = TransformPixelsToRowCol(neighbouringRoad.getPosition().y);
                int neighbouring_col = TransformPixelsToRowCol(neighbouringRoad.getPosition().x);
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
			case 1: ChoseRoadWithOneNeighbour(road, north, south, east, west, row, col); break;
			case 2: ChoseRoadWithTwoNeighbours(road, north, south, east, west); break;
			case 3: ChoseRoadWithThreeNeighbours(road, north, south, east, west); break;
			case 4: road.setTexture(&this->_data->assets.GetTexture("Intersection")); break;
			}
		}
	}
	/*Ustawia drodze odpowiedniπ teksturÍ w przypadku w ktÛrym droga ma tylko jednπ sπsiadujπcπ drogÍ*/
	void MapView::ChoseRoadWithOneNeighbour(sf::RectangleShape& road, std::shared_ptr<sf::RectangleShape> north, std::shared_ptr<sf::RectangleShape> south, std::shared_ptr<sf::RectangleShape> east, std::shared_ptr<sf::RectangleShape> west, int row, int col)
	{
        if (row != -2 && (col != 0 || col != _gridSize-1))
            road.setTexture(&this->_data->assets.GetTexture("Road"));
        
		road.setRotation(0);
		if (north) {
			road.setRotation(90.f);
		}
		else if (south) {
			road.setRotation(90.f);
		}
        
	}
	/*Ustawia drodze odpowiedniπ teksturÍ w przypadku w ktÛrym droga ma dwie sπsiadujπce drogi*/
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
	/*Ustawia drodze odpowiedniπ teksturÍ w przypadku w ktÛrym droga ma trzy sπsiadujπce drogi*/
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
	/*Usuwa drogÍ z mapy*/
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
    void MapView::UpdateIsDeletingCamera(int whichCamera){
        
    }
    void MapView::DeleteCamera(sf::Vector2f position){
        int i = 0;
        for (sf::RectangleShape camera : _cameras) {
            if (camera.getPosition().x - this->_cellSize / 2 == position.x && camera.getPosition().y - this->_cellSize / 2 == position.y){
                _cameras.erase(_cameras.begin() + i);
                camera.setTexture(NULL);
            }
            i++;
        }
        
//        _cameras.at(whichCamera-1).setTexture(NULL);
//        _cameras.erase(_roads.begin() + whichCamera-1);
//        CheckRoadsTexture();
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
		DrawVehicles();
        DrawCameras();
	}

    void MapView::zoomViewAt(sf::Vector2f pixel, float zoom)
    {
        if (zoom < 0){
            
            this->_mapView.zoom(1.f/abs(zoom));
        }
        else{
            this->_mapView.zoom(zoom);
        }

    }
    void MapView::Move(keysEnum key){
        
        switch (key){
        case LEFT: this->_mapView.move(-90.f, 0);
            break;
        case RIGHT: this->_mapView.move(90.f, 0);
            break;
        case UP: this->_mapView.move(0, -90.f);
            break;
        case DOWN: this->_mapView.move(0, 90.f);
            break;
            
        }
    }
	/*Odúwierza wartosÊ koordynatÛw obecnie klikniÍtego pola*/
	void MapView::UpdateSelectedCell(sf::Vector2i coords)
	{
		this->_row = coords.x;
		this->_col = coords.y;
	}
	/*Odswierza wszystkie komÛrki znajdujπce siÍ na mapie*/
	void MapView::UpdateCells(std::vector<Cell> cells)
	{
        this->_cells = cells;
	}
    void MapView::UpdateRoads(std::vector<sf::RectangleShape> roads)
    {
        this->_roads = roads;
    }
	/*Odúwierza wartosc zminnej decydujπcej o tym czy jestesmy w trybie rysowania drogi*/
	void MapView::UpdateIsDrawingRoad(bool isDrawingRoad)
	{
		this->isDrawingRoad = isDrawingRoad;
        this->isDeletingRoad = false;
        this->isSimulating = false;
	}
	/*Uaktualnia wartoúc zmiennej decydojacej o tym czy jesteúmy w trybie usuwania drogi*/
    void MapView::UpdateIsDeletingRoad(bool isDeletingRoad)
    {
        this->isDeletingRoad = isDeletingRoad;
        this->isDrawingRoad = false;
        this->isSimulating = false;
    }
	/*Uaktualnia wartoúc zmiennej decydojacej o tym czy jesteúmy w trybie symulacji*/
    void MapView::UpdateIsSimulating(bool isSimulating){
        this->isSimulating = isSimulating;
        this->isDrawingRoad = false;
        this->isDeletingRoad = false;
    }
    void MapView::UpdateIsAddingCamera(bool isAddingCamera, int whichCamera){
        this->isAddingCamera = isAddingCamera;
        this->isDrawingRoad = false;
        this->isDeletingRoad = false;
        this->_whichCamera = whichCamera;
        
    }
    void MapView::SaveToFile(){
        this->_data->machine.AddState(StateRef(new SaveState(this->_data, _cells, _gridSize)), false);
    }
	/*Uaktualnia listÍ samochodÛw znajdujπcych siÍ na ulicach*/
	void MapView::UpdateVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles)
	{
		this->_vehicles = vehicles;
	}

    std::vector<Cell> MapView::GetCells(){
        return _cells;
    }
	/*Zajmuje siÍ wstepnπ obs≥ugπ zdarzenia klikniÍcia na mapÍ*/
	sf::Vector2i MapView::HandleInput(sf::Vector2f mousePosition)
	{
		int possibleSellectedRow = (int)(mousePosition.y / this->_cellSize);
		int possibleSellectedCol = (int)(mousePosition.x / this->_cellSize);
		return sf::Vector2i(possibleSellectedRow, possibleSellectedCol);
	}
	/*Zwraca obiekt typu View reprezentujacy mapÍ*/
	sf::View MapView::GetView()
	{
		return this->_mapView;
	}
    std::ofstream& operator<< (std::ofstream& os, const MapView& currentMapView){
        os << currentMapView._gridSize << std::endl;
        for(auto p : currentMapView._cells)
            os << p.GetPosition().x <<" & "<< p.GetPosition().y<<" % "<<p._containsRoad<<std::endl;
        return os;
    }
	std::ostream& operator<<(std::ostream& os, const MapView&)
	{
		return os;
	}
}
