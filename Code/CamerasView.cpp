#include "CamerasView.h"
#include <iostream>
namespace ZPR {
	CamerasView::CamerasView(SimulatorDataRef data) : _data(data), _isSimulating(false)
	{
		this->_camerasView = sf::View(sf::FloatRect(0.f, 0.f, (float)((SCREEN_WIDTH - SCREEN_HEIGHT) / 2), (float)(SCREEN_HEIGHT)));
		this->_camerasView.setViewport(CalculateViewPort());
		this->_background.setPosition(0, 0);
		this->_background.setSize(this->_camerasView.getSize());
		this->_background.setFillColor(sf::Color(80, 80, 80));
        
        
        this->AddButtons();
        this->CamerasLabels("Camera 1: Disabled", 50);
        this->CamerasLabels("Camera 2: Disabled", 280);
        this->CamerasLabels("Camera 3: Disabled", 510);
        
	}
    void CamerasView::AddButtons(){
        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        for ( int i = 1; i<4; i++){
        this->_buttons.push_back(Button(sf::Vector2f(2*_camerasView.getSize().x/8, 230*i), buttonSize, "Add camera",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
            
            
        this->_buttons.push_back(Button(sf::Vector2f(6*_camerasView.getSize().x/8, 230*i), buttonSize, "Rotate",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
            //std::cout<<"Button "<<i<<" position Y: "<<_buttons.at(i-1).getPosition().y<<std::endl;
        }
        for (Button& button : _buttons){
            std::cout<<"Button position Y: "<<button.getPosition().y<<std::endl;
            std::cout<<"Button position X: "<<button.getPosition().x<<std::endl;
        }
        
        this->_buttons.push_back(Button(sf::Vector2f(_camerasView.getSize().x/2, 900), buttonSize, "Start simulation",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
    }
    void CamerasView::CamerasLabels(std::string text, int yPosition){
        sf::Text tempLabel;
        tempLabel.setFont(this->_data->assets.GetFont("Text font"));
        tempLabel.setCharacterSize(30);
        tempLabel.setString(text);
        tempLabel.setPosition(_camerasView.getSize().x/6, yPosition);
        this->_camerasLabels.push_back(tempLabel);
        
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
        for( sf::Text label : _camerasLabels)
        {
            this->_data->window.draw(label);
        }
}
    void CamerasView::ButtonsHandler(Button button, std::string label, int position, int labelPosition){
        if (this->_buttons.at(position).isPressed) {
            this->_buttons.at(position).setBackground(this->_data->assets.GetTexture("Button"));
            button.setText("Add camera");
            _camerasLabels.at(labelPosition).setString(label+"Disabled");
        }
        else{
            this->_buttons.at(position).setBackground(this->_data->assets.GetTexture("Button_pressed"));
            button.setText("Remove camera");
            _camerasLabels.at(labelPosition).setString(label+"Enabled");
        }
    }
    void CamerasView::HandleInput(){
        for (Button& button : this->_buttons){
            if (button.isClicked(sf::Mouse::Left, this->_data->window, this->_camerasView)){
                if (button.getText() == "Start simulation" || button.getText() == "Stop simulation"  ) {
                    if (this->_buttons.at(6).isPressed) {
                        this->_buttons.at(6).setBackground(this->_data->assets.GetTexture("Button"));
                        button.setText("Start simulation");
                    }
                    else{
                        this->_buttons.at(6).setBackground(this->_data->assets.GetTexture("Button_pressed"));
                        button.setText("Stop simulation");
                    }
                    
                    this->NotifyIsSimulating();
                }
                if (button.getPosition().x == 27 && button.getPosition().y == 209) {
                    this->ButtonsHandler(button, "Camera 1: ", 0, 0);
                }
                if (button.getPosition().x == 27 && button.getPosition().y == 439) {
                    this->ButtonsHandler(button, "Camera 2: ", 2, 1);
                }
                if (button.getPosition().x == 27 && button.getPosition().y == 669) {
                    this->ButtonsHandler(button, "Camera 3: ", 4, 2);
                }
                if (button.getPosition().x == 220.5 && button.getPosition().y == 209) {
                    
                }
                if (button.getPosition().x == 220.5 && button.getPosition().y == 439) {
                    
                }
                if (button.getPosition().x == 220.5 && button.getPosition().y == 669) {
                    
                }
                button.isPressed = !button.isPressed;
            }
        }
    }
}
