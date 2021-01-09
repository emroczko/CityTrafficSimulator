#include "cameras_subject.hpp"

namespace ZPR {
    /*Dodaje obserwatora*/
    void CamerasSubject::add(std::shared_ptr<CamerasObserver> obs)
    {
        this->_observers.push_back(obs);
    }
    void CamerasSubject::NotifyIsSimulating()
    {
        for (std::shared_ptr<CamerasObserver> obs : this->_observers) {
            obs->UpdateIsSimulating();
        }
    }
    void CamerasSubject::NotifyIsAddingCamera(int whichCamera)
    {
        for (std::shared_ptr<CamerasObserver> obs : this->_observers) {
            obs->UpdateIsAddingCamera(whichCamera);
        }
    }
    void CamerasSubject::NotifyIsDeletingCamera(int whichCamera)
    {
        for (std::shared_ptr<CamerasObserver> obs : this->_observers) {
            obs->UpdateIsDeletingCamera(whichCamera);
        }
    }
   
}
