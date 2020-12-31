
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
	/*Powiadamia obserwatoró o zmianie stanu kontenera zawierającego komórki*/
	void CreatorSubject::NotifyCells(std::vector<Cell> cells)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateCells(cells);
		}
	}
	/*Powiadamia obserwatorów o zmianie stanu rysowania drogi (włączony/wyłączony)*/
	void CreatorSubject::NotifyIsDrawingRoad(bool isDrawingRoad)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateIsDrawingRoad(isDrawingRoad);
		}
	}
	/*Powiadamia obserwatorów o zmianie stanu usuwania drogi (włączony/wyłączony)*/
    void CreatorSubject::NotifyIsDeletingRoad(bool isDeletingRoad)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
            obs->UpdateIsDeletingRoad(isDeletingRoad);
        }
    }
	/*Powiadamia obserwatorów o zmianie stanu symulacji (włączona/wyłączona)*/
    void CreatorSubject::NotifyIsSimulating(bool isSimulating)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
            obs->UpdateIsSimulating(isSimulating);
        }
    }
	/*Powiadamia obserwatorów o zmianie stanu kontenera zawierającego pojazdy*/
	void CreatorSubject::NotifyVehicles(std::vector<std::shared_ptr<Vehicle>> vehicles)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateVehicles(vehicles);
		}
	}
}
