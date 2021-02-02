/**
 * cameras_subject.hpp
 * Header of CamerasSubject class.
 */

#pragma once
#include "../observers/cameras_observer.hpp"
#include <vector>
#include <memory>

namespace zpr {

    /**
     * Class responsible for notifying the observers.
     */
    class CamerasSubject
    {
    public:
        void add(std::shared_ptr<CamerasObserver> observer);
        void notifyIsSimulating();
        void notifyIsAddingCamera(int which_camera);
        void notifyIsDeletingCamera(int which_camera);
        virtual ~CamerasSubject() {};
    private:
        std::vector<std::shared_ptr<CamerasObserver>> observers_;
    };
}
