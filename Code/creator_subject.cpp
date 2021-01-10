
#include "creator_subject.hpp" 

namespace zpr {
	/*Dodaje obserwatora*/
	void CreatorSubject::add(std::shared_ptr<CreatorObserver> obs)
	{
		this->observers_.push_back(obs);
	}
	/*Powiadamia obserwator�w o zmianie koordynat�w obecnie wybranek kom�rki*/
	void CreatorSubject::notifySelectedCell(sf::Vector2i coords)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->observers_) {
			obs->updateSelectedCell(coords);
		}
	}
	/*Powiadamia obserwator� o zmianie stanu kontenera zawieraj�cego kom�rki*/
	void CreatorSubject::notifyCells(std::vector<Cell> cells)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->observers_) {
			obs->updateCells(cells);

		}
	}
   
	/*Powiadamia obserwator�w o zmianie stanu rysowania drogi (w��czony/wy��czony)*/
	void CreatorSubject::notifyIsDrawingRoad(bool isDrawingRoad)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->observers_) {
			obs->updateIsDrawingRoad(isDrawingRoad);
		}
	}
	/*Powiadamia obserwator�w o zmianie stanu usuwania drogi (w��czony/wy��czony)*/
    void CreatorSubject::notifyIsDeletingRoad(bool isDeletingRoad)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->observers_) {
            obs->updateIsDeletingRoad(isDeletingRoad);
        }
    }
    void CreatorSubject::notifyIsAddingCamera(bool isAddingCamera, int whichCamera, int row, int col)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->observers_) {
            obs->updateIsAddingCamera(isAddingCamera, whichCamera, row, col);
        }
    }
    void CreatorSubject::notifyIsDeletingCamera(int whichCamera)
    {
        for (std::shared_ptr<CreatorObserver> obs : this->observers_) {
            obs->updateIsDeletingCamera(whichCamera);
        }
    }
    void CreatorSubject::notifySave()
    {
        for (std::shared_ptr<CreatorObserver> obs : this->observers_) {
            obs->saveToFile();
        }
    }
    
}
