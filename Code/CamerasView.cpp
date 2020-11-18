#include "CamerasView.h"
namespace ZPR {
	CamerasView::CamerasView(SimulatorDataRef data) : _data(data)
	{
		this->_camerasView = sf::View(sf::FloatRect(0.f, 0.f, (float)((SCREEN_WIDTH - SCREEN_HEIGHT) / 2), (float)(SCREEN_HEIGHT)));
		this->_camerasView.setViewport(CalculateViewPort());
		this->_background.setPosition(0, 0);
		this->_background.setSize(this->_camerasView.getSize());
		this->_background.setFillColor(sf::Color(80, 80, 80));
	}

	sf::FloatRect CamerasView::CalculateViewPort()
	{
		float rectWidth = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
		float rectLeft = rectWidth + (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
		return sf::FloatRect(rectLeft, 0.f, rectWidth, 1.f);
	}

	void CamerasView::Draw()
	{
		this->_data->window.setView(this->_camerasView);
		this->_data->window.draw(this->_background);
	}
}
