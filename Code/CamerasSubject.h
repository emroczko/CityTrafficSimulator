#pragma once
#include "CamerasObserver.h"
#include <vector>
#include <memory>

namespace ZPR {
    class CamerasSubject
    {
    public:
        void add(std::shared_ptr<CamerasObserver> obs);
        void NotifyIsSimulating();
        void NotifyIsAddingCamera(int whichCamera);
        void NotifyIsDeletingCamera(int whichCamera);
        virtual ~CamerasSubject() {};
    private:
        std::vector<std::shared_ptr<CamerasObserver>> _observers;
    };
}
