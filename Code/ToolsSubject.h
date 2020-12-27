#pragma once
#include "ToolsObserver.h"
#include <vector>
#include <memory>

namespace ZPR {
	class ToolsSubject
	{
	public:
		void add(std::shared_ptr<ToolsObserver> obs);
		void NotifyIsDrawingRoad();
		virtual ~ToolsSubject() {};
	private:
		std::vector<std::shared_ptr<ToolsObserver>> _observers;
	};
}

