#pragma once
#include "tools_observer.hpp"
#include <vector>
#include <memory>

namespace ZPR {
	class ToolsSubject
	{
	public:
		void add(std::shared_ptr<ToolsObserver> obs);
		void NotifyIsDrawingRoad();
        void NotifyIsDeletingRoad();
        void NotifySave();
		virtual ~ToolsSubject() {};
	private:
		std::vector<std::shared_ptr<ToolsObserver>> _observers;
	};
}

