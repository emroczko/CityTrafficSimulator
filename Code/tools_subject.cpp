#include "tools_subject.hpp"

namespace zpr {
	/*Dodaje obserwatora*/
	void ToolsSubject::add(std::shared_ptr<ToolsObserver> observer)
	{
		this->observers_.push_back(observer);
	}
	/*Powiadamia obserwatorów o przyciœniêciu przycisku zmieniaj¹cego stanu rysowania drogi (w³¹czony/wy³¹czony)*/
	void ToolsSubject::notifyIsDrawingRoad()
	{
		for (std::shared_ptr<ToolsObserver> obs : this->observers_) {
			obs->updateIsDrawingRoad();
		}
	}
	/*Powiadamia obserwatorów o przyciœniêciu przycisku zmieniaj¹cego stanu usuwania drogi (w³¹czony/wy³¹czony)*/
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
