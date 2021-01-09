
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
    void CreatorSubject::NotifyIsAddingCamera(bool isAddingCamera, int whichCamera, int row, int col)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
            obs->UpdateIsAddingCamera(isAddingCamera, whichCamera, row, col);
        }
    }
    void CreatorSubject::NotifyIsDeletingCamera(int whichCamera)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
            obs->UpdateIsDeletingCamera(whichCamera);
        }
    }
    void CreatorSubject::NotifySave()
    {
        for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
            obs->SaveToFile();
        }
    }
    
}
