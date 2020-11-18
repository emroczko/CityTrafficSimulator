#include "ToolsView.h"

namespace ZPR {
	ToolsView::ToolsView(SimulatorDataRef data) : _data(data)
	{
		this->_toolsView = sf::View(sf::FloatRect(0.f, 0.f, (float)((SCREEN_WIDTH - SCREEN_HEIGHT) / 2), (float)(SCREEN_HEIGHT)));
		this->_toolsView.setViewport(CalculateViewPort());
		this->_background.setPosition(0, 0);
		this->_background.setSize(this->_toolsView.getSize());
		this->_background.setFillColor(sf::Color(80, 80, 80));
	}

	sf::FloatRect ToolsView::CalculateViewPort()
	{
		float rectWidth = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH)/2;
		float rectLeft = 0.f;
		return sf::FloatRect(rectLeft, 0.f, rectWidth, 1.f);
	}

	void ToolsView::Draw()
	{
		this->_data->window.setView(this->_toolsView);
		this->_data->window.draw(this->_background);
		DrawButtons();
	}

	void ToolsView::DrawButtons()
	{
		for (Button button: _buttons)
		{
			this->_data->window.draw(button);
		}
	}

}