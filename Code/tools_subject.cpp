#include "tools_subject.hpp"

namespace zpr {
	/*Dodaje obserwatora*/
	void ToolsSubject::add(std::shared_ptr<ToolsObserver> observer)
	{
		this->observers_.push_back(observer);
	}
	/*Powiadamia obserwator�w o przyci�ni�ciu przycisku zmieniaj�cego stanu rysowania drogi (w��czony/wy��czony)*/
	void ToolsSubject::notifyIsDrawingRoad()
	{
		for (std::shared_ptr<ToolsObserver> obs : this->observers_) {
			obs->updateIsDrawingRoad();
		}
	}
	/*Powiadamia obserwator�w o przyci�ni�ciu przycisku zmieniaj�cego stanu usuwania drogi (w��czony/wy��czony)*/
    void ToolsSubject::notifyIsDeletingRoad()
    {
        for (std::shared_ptr<ToolsObserver> obs : this->observers_) {
            obs->updateIsDeletingRoad();
        }
    }
    void ToolsSubject::notifySave()
    {
        for (std::shared_ptr<ToolsObserver> obs : this->observers_) {
            obs->saveToFile();
        }
    }
}
