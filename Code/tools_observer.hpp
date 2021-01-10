#pragma once

namespace zpr {
    class ToolsObserver
    {
    public:
        virtual void updateIsDrawingRoad() = 0;
        virtual void updateIsDeletingRoad() = 0;
        virtual void saveToFile() = 0;
        virtual ~ToolsObserver() {}
    };
}

