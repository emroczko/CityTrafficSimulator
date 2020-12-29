#include "CamerasSubject.h"

namespace ZPR {
    void CamerasSubject::add(std::shared_ptr<CamerasObserver> obs)
    {
        this->_observers.push_back(obs);
    }

    void CamerasSubject::NotifyIsSimulating()
    {
        for (std::shared_ptr<CamerasObserver> obs : this->_observers) {
            obs->UpdateIsDrawingRoad();
        }
    }
   
}
