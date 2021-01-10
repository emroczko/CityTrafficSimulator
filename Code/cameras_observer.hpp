#pragma once

namespace zpr {
    class CamerasObserver
    {
    public:
        virtual void updateIsSimulating() = 0;
        virtual void updateIsAddingCamera(int which_camera) = 0;
        virtual void updateIsDeletingCamera(int which_camera) = 0;
        virtual ~CamerasObserver() {}
    };
}

