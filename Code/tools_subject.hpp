#pragma once
#include "tools_observer.hpp"
#include <vector>
#include <memory>

namespace zpr {
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

