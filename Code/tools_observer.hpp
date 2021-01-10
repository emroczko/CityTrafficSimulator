/**
 * tools_observer.hpp
 * Header of ToolsObserver virtual class.
 */
#pragma once

namespace zpr {

    /**
     * Virtual class responsible for being an observer for ToolsView class. 
     */
    class ToolsObserver
    {
    public:
        virtual void updateIsDrawingRoad() = 0;
        virtual void updateIsDeletingRoad() = 0;
        virtual void saveToFile() = 0;
        virtual ~ToolsObserver() {}
    };
}

