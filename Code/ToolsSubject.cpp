#include "ToolsSubject.h"

namespace ZPR {
	/*Dodaje obserwatora*/
	void ToolsSubject::add(std::shared_ptr<ToolsObserver> obs)
	{
		this->_observers.push_back(obs);
	}
	/*Powiadamia obserwatorów o przyciœniêciu przycisku zmieniaj¹cego stanu rysowania drogi (w³¹czony/wy³¹czony)*/
	void ToolsSubject::NotifyIsDrawingRoad()
	{
		for (std::shared_ptr<ToolsObserver> obs : this->_observers) {
			obs->UpdateIsDrawingRoad();
		}
	}
	/*Powiadamia obserwatorów o przyciœniêciu przycisku zmieniaj¹cego stanu usuwania drogi (w³¹czony/wy³¹czony)*/
    void ToolsSubject::NotifyIsDeletingRoad()
    {
        for (std::shared_ptr<ToolsObserver> obs : this->_observers) {
            obs->UpdateIsDeletingRoad();
        }
    }
}
