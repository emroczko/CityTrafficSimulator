#pragma once
#include "CreatorObserver.h"
#include "Cell.h"
#include <vector>

namespace ZPR {
    class CreatorSubject
    {
    public:
        void add(std::shared_ptr<CreatorObserver> obs);
        void NotifySelectedCell(sf::Vector2i coords);
        void NotifyCells(std::vector<Cell> cells);
        void NotifySave();
        void NotifyIsDrawingRoad(bool isDrawingRoad);
        void NotifyIsAddingCamera(bool isAddingCamera, int whichCamera);
        void NotifyIsDeletingCamera(int whichCamera);
        void NotifyIsDeletingRoad(bool isDeletingRoad);
        void NotifyIsSimulating(bool isSimulating);
        virtual ~CreatorSubject() {}
    private:
        std::vector<std::shared_ptr<CreatorObserver> > _observers;
    };
}

