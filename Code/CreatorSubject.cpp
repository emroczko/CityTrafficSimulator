
#include "CreatorSubject.h" 

namespace ZPR {
	void CreatorSubject::add(std::shared_ptr<CreatorObserver> obs)
	{
		this->_observers.push_back(obs);
	}

	void CreatorSubject::NotifySelectedCell(sf::Vector2i coords)
	{
		for (std::shared_ptr<CreatorObserver> obs : this->_observers) {
			obs->UpdateSelectedCell(coords);
		}
	}

	void CreatorSubject::NotifyCells(std::vector<Cell> cells)
	{
		int a = _observers.size();
		int b = 0;
		//obs->UpdateCells(cells);
	}

}