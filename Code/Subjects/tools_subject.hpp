/**
 * tools_subject.hpp
 * Header of ToolsSubject class.
 */
#pragma once
#include "../observers/tools_observer.hpp"
#include <vector>
#include <memory>

namespace zpr {

    /**
     * Class responsible for notifying the observers.
     */
	class ToolsSubject
	{
	public:
		void add(std::shared_ptr<ToolsObserver> observer);
		void notifyIsDrawingRoad();
        void notifyIsDeletingRoad();
        void notifySave();
		virtual ~ToolsSubject() {};
	private:
		std::vector<std::shared_ptr<ToolsObserver>> observers_;
	};
}

