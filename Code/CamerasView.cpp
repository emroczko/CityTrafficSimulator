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
        
        for (int i = 0; i<3; i++){
            this->_camerasOn.push_back(false);
        }
        
	}
    void CamerasView::AddButtons(){
        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        for ( int i = 1; i<4; i++){
        this->_buttons.push_back(Button(sf::Vector2f(_camerasView.getSize().x/2, 230*i), buttonSize, "Add camera "+std::to_string(i),
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
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
    
            
        
    
    
    void CamerasView::UpdateIsAddingCamera(bool isAddingCamera, int whichCamera){
        if(!isAddingCamera){
            this->_camerasOn.at(whichCamera-1) = true;
            this->_buttons.at(whichCamera-1).setText("Remove camera "+std::to_string(whichCamera));
            this->_buttons.at(whichCamera-1).setBackground(this->_data->assets.GetTexture("Button"));
            _camerasLabels.at(whichCamera-1).setString("Camera "+std::to_string(whichCamera)+": Enabled");
        }else{
            this->_buttons.at(whichCamera-1).setBackground(this->_data->assets.GetTexture("Button_pressed"));
        }
    }
    void CamerasView::UpdateIsDeletingCamera(int whichCamera){
        this->_camerasOn.at(whichCamera-1) = false;
        this->_buttons.at(whichCamera-1).setText("Add camera "+std::to_string(whichCamera));
        this->_buttons.at(whichCamera-1).setBackground(this->_data->assets.GetTexture("Button"));
        _camerasLabels.at(whichCamera-1).setString("Camera "+std::to_string(whichCamera)+": Disabled");
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
                if (button.getText() == "Add camera 1") {
                    //this->ButtonsHandler(button, "Camera 1: ", 0, 0);
                    this->NotifyIsAddingCamera(1);
                    
                }
                if (button.getText() == "Add camera 2") {
                   // this->ButtonsHandler(button, "Camera 2: ", 1, 1);
                    this->NotifyIsAddingCamera(2);
                }
                if (button.getText() == "Add camera 3") {
                    //this->ButtonsHandler(button, "Camera 3: ", 2, 2);
                    this->NotifyIsAddingCamera(3);
                }
                if (button.getText() == "Remove camera 1") {
                    //this->ButtonsHandler(button, "Camera 1: ", 0, 0);
                    this->NotifyIsDeletingCamera(1);
                    
                }
                if (button.getText() == "Remove camera 2") {
                   // this->ButtonsHandler(button, "Camera 2: ", 1, 1);
                    this->NotifyIsDeletingCamera(2);
                }
                if (button.getText() == "Remove camera 3") {
                    //this->ButtonsHandler(button, "Camera 3: ", 2, 2);
                    this->NotifyIsDeletingCamera(3);
                }
                button.isPressed = !button.isPressed;
                
            }
        }
    }
}
