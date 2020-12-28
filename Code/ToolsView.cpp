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
        this->_data->assets.LoadTexture("Button_pressed", BUTTON_PRESSED_FILEPATH);
        this->_data->assets.LoadFont("Text font", TEXT_FONT_FILEPATH);

        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        this->_buttons.push_back(Button(sf::Vector2f(_toolsView.getSize().x/2, 100), buttonSize, "Create new street",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
   
        this->_buttons.push_back(Button(sf::Vector2f(_toolsView.getSize().x/2, 300), buttonSize, "Delete streets",
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

    bool ToolsView::isClicked(sf::Vector2i &mousePosition){
    
        if(_toolsView.getViewport().contains(static_cast<float>(mousePosition.x)/SCREEN_WIDTH, static_cast<float>(mousePosition.y)/SCREEN_HEIGHT))
            return true;
        else
            return false;
    }
    void ToolsView::HandleInput(){
        for (Button& button : this->_buttons){
            if (button.isClicked(sf::Mouse::Left, this->_data->window, this->_toolsView)){
                if (button.getText() == "Create new street") {
                    if (this->_buttons.at(1).isPressed) {
                        this->_buttons.at(1).setBackground(this->_data->assets.GetTexture("Button"));
                    }
                    this->_buttons.at(1).isPressed = false;
                    this->NotifyIsDrawingRoad();
                }

                if (button.getText() == "Delete streets") {
                    if (this->_buttons.at(0).isPressed) {
                        this->_buttons.at(0).setBackground(this->_data->assets.GetTexture("Button"));
                    }
                    this->_buttons.at(0).isPressed = false;
                    this->NotifyIsDeletingRoad();
                }

                //Tu doda³em ¿eby siê zmienia³ bg przycisku jak siê kliknie i odkliknie //
                button.isPressed = !button.isPressed;
                if (button.isPressed) {
                    button.setBackground(this->_data->assets.GetTexture("Button_pressed"));
                }
                else {
                    button.setBackground(this->_data->assets.GetTexture("Button"));
                }
            }
        }
    }

	void ToolsView::DrawButtons()
	{
		for (Button button: _buttons)
		{
			this->_data->window.draw(button);
		}
	}
    sf::View ToolsView::GetView()
    {
        return this->_toolsView;
    }

}
