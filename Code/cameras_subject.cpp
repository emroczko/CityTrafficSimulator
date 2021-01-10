#include "cameras_subject.hpp"

namespace zpr {
    /*Dodaje obserwatora*/
    void CamerasSubject::add(std::shared_ptr<CamerasObserver> observer)
    {
        this->observers_.push_back(observer);
    }
    void CamerasSubject::notifyIsSimulating()
    {
        for (std::shared_ptr<CamerasObserver> observer : this->observers_) {
            observer->updateIsSimulating();
        }
    }
    void CamerasSubject::notifyIsAddingCamera(int which_camera)
    {
        for (std::shared_ptr<CamerasObserver> observer : this->observers_) {
            observer->updateIsAddingCamera(which_camera);
        }
    }
    void CamerasSubject::notifyIsDeletingCamera(int which_camera)
    {
        for (std::shared_ptr<CamerasObserver> observer : this->observers_) {
            observer->updateIsDeletingCamera(which_camera);
        }
    }
   
}
