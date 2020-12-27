#pragma once

namespace ZPR {
    class ToolsObserver
    {
    public:
        virtual void UpdateIsDrawingRoad() = 0;
        virtual ~ToolsObserver() {}
    };
}

