/**
 * cameras_observer.hpp
 * Header of CamerasObserver virtual class.
 */

#pragma once

namespace zpr {

    /**
     * Virtual class responsible for being an observer for CamerasView class.
     */
    class CamerasObserver
    {
    public:
        virtual void updateIsSimulating() {}
        virtual void updateIsAddingCamera(int which_camera) {}
        virtual void updateIsDeletingCamera(int which_camera) {}
        virtual ~CamerasObserver() {}
    };
}

