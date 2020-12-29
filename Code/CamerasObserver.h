#pragma once

namespace ZPR {
    class CamerasObserver
    {
    public:
        virtual void UpdateIsSimulating() = 0;
        virtual ~CamerasObserver() {}
    };
}

