
#include "CreatorSubject.h" 

namespace ZPR {
	/*Dodaje obserwatora*/
	void CreatorSubject::add(std::shared_ptr<CreatorObserver> obs)
	{
		this->_observers.push_back(obs);
	}
	/*Powiadamia obserwator�w o zmianie koordynat�w obecnie wybranek kom�rki*/
	void CreatorSubject::NotifySelectedCell(sf::Vector2i coords)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateSelectedCell(coords);
		}
	}
	/*Powiadamia obserwator� o zmianie stanu kontenera zawieraj�cego kom�rki*/
	void CreatorSubject::NotifyCells(std::vector<Cell> cells)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateCells(cells);
		}
	}
	/*Powiadamia obserwator�w o zmianie stanu rysowania drogi (w��czony/wy��czony)*/
	void CreatorSubject::NotifyIsDrawingRoad(bool isDrawingRoad)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateIsDrawingRoad(isDrawingRoad);
		}
	}
	/*Powiadamia obserwator�w o zmianie stanu usuwania drogi (w��czony/wy��czony)*/
    void CreatorSubject::NotifyIsDeletingRoad(bool isDeletingRoad)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
            obs->UpdateIsDeletingRoad(isDeletingRoad);
        }
    }
	/*Powiadamia obserwator�w o zmianie stanu symulacji (w��czona/wy��czona)*/
    void CreatorSubject::NotifyIsSimulating(bool isSimulating)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
            obs->UpdateIsSimulating(isSimulating);
        }
    }
	/*Powiadamia obserwator�w o zmianie stanu kontenera zawieraj�cego pojazdy*/
	void CreatorSubject::NotifyVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateVehicles(vehicles);
		}
	}
}
