
#include "CreatorSubject.h" 

namespace ZPR {
	/*Dodaje obserwatora*/
	void CreatorSubject::add(std::shared_ptr<CreatorObserver> obs)
	{
		this->_observers.push_back(obs);
	}
	/*Powiadamia obserwatorów o zmianie koordynatów obecnie wybranek komórki*/
	void CreatorSubject::NotifySelectedCell(sf::Vector2i coords)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateSelectedCell(coords);
		}
	}
	/*Powiadamia obserwatoró o zmianie stanu kontenera zawieraj¹cego komórki*/
	void CreatorSubject::NotifyCells(std::vector<Cell> cells)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateCells(cells);
		}
	}
	/*Powiadamia obserwatorów o zmianie stanu rysowania drogi (w³¹czony/wy³¹czony)*/
	void CreatorSubject::NotifyIsDrawingRoad(bool isDrawingRoad)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateIsDrawingRoad(isDrawingRoad);
		}
	}
	/*Powiadamia obserwatorów o zmianie stanu usuwania drogi (w³¹czony/wy³¹czony)*/
    void CreatorSubject::NotifyIsDeletingRoad(bool isDeletingRoad)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
            obs->UpdateIsDeletingRoad(isDeletingRoad);
        }
    }
	/*Powiadamia obserwatorów o zmianie stanu symulacji (w³¹czona/wy³¹czona)*/
    void CreatorSubject::NotifyIsSimulating(bool isSimulating)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
            obs->UpdateIsSimulating(isSimulating);
        }
    }
	/*Powiadamia obserwatorów o zmianie stanu kontenera zawieraj¹cego pojazdy*/
	void CreatorSubject::NotifyVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateVehicles(vehicles);
		}
	}
}
