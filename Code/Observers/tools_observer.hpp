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
        virtual void updateIsDrawingRoad() {}
        virtual void updateIsDeletingRoad() {}
        virtual void saveToFile() {}
        virtual ~ToolsObserver() {}
    };
}

