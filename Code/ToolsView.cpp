#include "ToolsView.h"

namespace ZPR {
	ToolsView::ToolsView(SimulatorDataRef data) : _data(data)
	{
		this->_toolsView = sf::View(sf::FloatRect(0.f, 0.f, (float)((SCREEN_WIDTH - SCREEN_HEIGHT) / 2), (float)(SCREEN_HEIGHT)));
		this->_toolsView.setViewport(CalculateViewPort());
		this->_background.setPosition(0, 0);
		this->_background.setSize(this->_toolsView.getSize());
		this->_background.setFillColor(sf::Color(80, 80, 80));
        
        this->_data->assets.LoadTexture("Button", BUTTON_FILEPATH);
        this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);

        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        this->_buttons.push_back(Button(sf::Vector2f(_toolsView.getSize().x/2, 100), buttonSize, "Create new street",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
	}

	sf::FloatRect ToolsView::CalculateViewPort()
	{
		
        float rectWidth = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
        float rectLeft = rectWidth + (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
        return sf::FloatRect(rectLeft, 0.f, rectWidth, 1.f);
	}

	void ToolsView::Draw()
	{
		this->_data->window.setView(this->_toolsView);
		this->_data->window.draw(this->_background);
		DrawButtons();
	}
    void ToolsView::NotifyCreateHandler(){
    
    }

    
    

	void ToolsView::DrawButtons()
	{
		for (Button button: _buttons)
		{
			this->_data->window.draw(button);
		}
	}

}
