#include "CamerasView.h"
namespace ZPR {
	CamerasView::CamerasView(SimulatorDataRef data) : _data(data), _isSimulating(false)
	{
		this->_camerasView = sf::View(sf::FloatRect(0.f, 0.f, (float)((SCREEN_WIDTH - SCREEN_HEIGHT) / 2), (float)(SCREEN_HEIGHT)));
		this->_camerasView.setViewport(CalculateViewPort());
		this->_background.setPosition(0, 0);
		this->_background.setSize(this->_camerasView.getSize());
		this->_background.setFillColor(sf::Color(80, 80, 80));
        
        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        this->_buttons.push_back(Button(sf::Vector2f(_camerasView.getSize().x/2, 100), buttonSize, "Add Camera",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        this->_buttons.push_back(Button(sf::Vector2f(_camerasView.getSize().x/2, 800), buttonSize, "Start simulation",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        
        
	}

	sf::FloatRect CamerasView::CalculateViewPort()
	{
        float rectWidth = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH)/2;
        float rectLeft = 0.f;
        return sf::FloatRect(rectLeft, 0.f, rectWidth, 1.f);
        
	}

    bool CamerasView::isClicked(sf::Vector2i &mousePosition){

        if(_camerasView.getViewport().contains(static_cast<float>(mousePosition.x)/SCREEN_WIDTH, static_cast<float>(mousePosition.y)/SCREEN_HEIGHT))
        return true;
     else
        return false;
    }
	void CamerasView::Draw()
	{
		this->_data->window.setView(this->_camerasView);
		this->_data->window.draw(this->_background);
        DrawButtons();
	}
    void CamerasView::DrawButtons()
    {
        for (Button button: _buttons)
        {
            this->_data->window.draw(button);
        }
}
    void CamerasView::HandleInput(){
        for (Button& button : this->_buttons){
            if (button.isClicked(sf::Mouse::Left, this->_data->window, this->_camerasView)){
                if (button.getText() == "Start simulation" || button.getText() == "Stop simulation"  ) {
                    if (this->_buttons.at(1).isPressed) {
                        this->_buttons.at(1).setBackground(this->_data->assets.GetTexture("Button"));
                        button.setText("Start simulation");
                        //this->NotifyIsSimulating(false);
                    }
                    else{
                        this->_buttons.at(1).setBackground(this->_data->assets.GetTexture("Button_pressed"));
                        button.setText("Stop simulation");
                        //this->NotifyIsSimulating(true);
                    }
                    this->NotifyIsSimulating();
                }
                button.isPressed = !button.isPressed;
            }
        }
    }
}
