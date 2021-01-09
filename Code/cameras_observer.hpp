#pragma once

namespace ZPR {
    class CamerasObserver
    {
    public:
        virtual void UpdateIsSimulating() = 0;
        virtual void UpdateIsAddingCamera(int whichCamera) = 0;
        virtual void UpdateIsDeletingCamera(int whichCamera) = 0;
        virtual ~CamerasObserver() {}
    };
}

