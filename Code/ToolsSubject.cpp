#include "ToolsSubject.h"

namespace ZPR {
	void ToolsSubject::add(std::shared_ptr<ToolsObserver> obs)
	{
		this->_observers.push_back(obs);
	}

	void ToolsSubject::NotifyIsDrawingRoad()
	{
		for (std::shared_ptr<ToolsObserver> obs : this->_observers) {
			obs->UpdateIsDrawingRoad();
		}
	}
    void ToolsSubject::NotifyIsDeletingRoad()
    {
        for (std::shared_ptr<ToolsObserver> obs : this->_observers) {
            obs->UpdateIsDeletingRoad();
        }
    }
}
