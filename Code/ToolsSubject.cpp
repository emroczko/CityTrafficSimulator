#include "ToolsSubject.h"

namespace ZPR {
	/*Dodaje obserwatora*/
	void ToolsSubject::add(std::shared_ptr<ToolsObserver> obs)
	{
		this->_observers.push_back(obs);
	}
	/*Powiadamia obserwator�w o przyci�ni�ciu przycisku zmieniaj�cego stanu rysowania drogi (w��czony/wy��czony)*/
	void ToolsSubject::NotifyIsDrawingRoad()
	{
		for (std::shared_ptr<ToolsObserver> obs : this->_observers) {
			obs->UpdateIsDrawingRoad();
		}
	}
	/*Powiadamia obserwator�w o przyci�ni�ciu przycisku zmieniaj�cego stanu usuwania drogi (w��czony/wy��czony)*/
    void ToolsSubject::NotifyIsDeletingRoad()
    {
        for (std::shared_ptr<ToolsObserver> obs : this->_observers) {
            obs->UpdateIsDeletingRoad();
        }
    }
}
