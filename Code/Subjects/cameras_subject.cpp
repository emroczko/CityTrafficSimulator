/**
 * cameras_subject.cpp
 * Implementation of CamerasSubject class.
 */

#include "cameras_subject.hpp"

namespace zpr {

    /**
     * Method which adds observers to vector.
     * @param observer - CamerasView class observer.
     */
    void CamerasSubject::add(std::shared_ptr<CamerasObserver> observer)
    {
        this->observers_.push_back(observer);
    }

    /**
     * Method which notifies observers when simulation starts or ends (when button "Start/Stop simulation" was clicked).
     */
    void CamerasSubject::notifyIsSimulating()
    {
        for (std::shared_ptr<CamerasObserver> observer : this->observers_) {
            observer->updateIsSimulating();
        }
    }

    /**
     * Method which notifies observers when user is adding a camera.
     * @param which_camera - Being added camera number.
     */
    void CamerasSubject::notifyIsAddingCamera(int which_camera)
    {
        for (std::shared_ptr<CamerasObserver> observer : this->observers_) {
            observer->updateIsAddingCamera(which_camera);
        }
    }

    /**
     * Method which notifies observers when user deletes a camera.
     * @param which_camera - Being deleted camera number.
     */
    void CamerasSubject::notifyIsDeletingCamera(int which_camera)
    {
        for (std::shared_ptr<CamerasObserver> observer : this->observers_) {
            observer->updateIsDeletingCamera(which_camera);
        }
    }
   
}
