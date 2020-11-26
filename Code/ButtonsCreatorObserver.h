#pragma once

namespace ZPR {
    class ButtonsCreatorObserver
    {
    public:
        virtual void UpdateCreateNewStreets() = 0;
        virtual ~ButtonsCreatorObserver() {}
    };
}

