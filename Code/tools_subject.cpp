/**
 * tools_subject.cpp
 * Implementation of ToolsSubject class.
 */

#include "tools_subject.hpp"

namespace zpr {
    
    /**
     * Method which adds observers to vector.
     * @param observer - ToolsView class observer.
     */
	void ToolsSubject::add(std::shared_ptr<ToolsObserver> observer)
	{
		this->observers_.push_back(observer);
	}


    /**
     * Method which notifies observers when road are being drawn or stop being drawn (when button "Create new street" was clicked).
     */
	void ToolsSubject::notifyIsDrawingRoad()
	{
		for (std::shared_ptr<ToolsObserver> observer : this->observers_) {
			observer->updateIsDrawingRoad();
		}
	}

    /**
     * Method which notifies observers when roads are being deleting or stop being deleting (when button "Delete street" was clicked).
     */
    void ToolsSubject::notifyIsDeletingRoad()
    {
        for (std::shared_ptr<ToolsObserver> observer : this->observers_) {
            observer->updateIsDeletingRoad();
        }
    }

    /**
     * Method which notifies observers when save button is clicked.
     */
    void ToolsSubject::notifySave()
    {
        for (std::shared_ptr<ToolsObserver> observer : this->observers_) {
            observer->saveToFile();
        }
    }
}
