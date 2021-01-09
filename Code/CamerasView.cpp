#include "CamerasView.h"
#include <iostream>
namespace ZPR {
CamerasView::CamerasView(SimulatorDataRef data) : _data(data), _isSimulating(false), _isAddingCamera(false)
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
        this->CamerasLabels("Cars passed: 0", 100);
        this->CamerasLabels("Cars passed: 0", 330);
        this->CamerasLabels("Cars passed: 0", 560);
        this->CamerasLabels("Trucks passed: 0", 150);
        this->CamerasLabels("Trucks passed: 0", 380);
        this->CamerasLabels("Trucks passed: 0", 610);
        

        for (int i = 0; i < 3; i++) {
            this->_camerasOn.push_back(false);
        }
        
        this->InitializeVehiclesCounters();
    }

    void CamerasView::InitializeVehiclesCounters(){
        for (int i = 0; i < 3; i++) {
            _numberOfCars[i] = 0;
            _numberOfTrucks[i] = 0;
            this->_camerasLabels.at(i + 3).setString("Cars passed: " + std::to_string(this->_numberOfCars[i]));
            this->_camerasLabels.at(i + 6).setString("Trucks passed: " + std::to_string(this->_numberOfTrucks[i]));
        }
    }
    void CamerasView::AddButtons() {
        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        for (int i = 1; i < 4; i++) {
            this->_buttons.push_back(Button(sf::Vector2f(2*_camerasView.getSize().x / 8, 230 * i), buttonSize, "Add camera " + std::to_string(i),
                this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
            this->_removeButtons.push_back(Button(sf::Vector2f(6*_camerasView.getSize().x / 8, 230 * i), buttonSize, "Remove camera " + std::to_string(i),
                this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
        }
        

        this->_buttons.push_back(Button(sf::Vector2f(_camerasView.getSize().x / 2, 900), buttonSize, "Start simulation",
            this->_data->assets.GetFont("Text font"), fontSize, sf::Color::White, this->_data->assets.GetTexture("Button")));
    }
    void CamerasView::CamerasLabels(std::string text, int yPosition) {
        sf::Text tempLabel;
        tempLabel.setFont(this->_data->assets.GetFont("Text font"));
        tempLabel.setCharacterSize(30);
        tempLabel.setString(text);
        tempLabel.setPosition(_camerasView.getSize().x / 6, yPosition);
        this->_camerasLabels.push_back(tempLabel);

    }
    sf::FloatRect CamerasView::CalculateViewPort()
    {
        float rectWidth = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
        float rectLeft = 0.f;
        return sf::FloatRect(rectLeft, 0.f, rectWidth, 1.f);

    }

    bool CamerasView::isClicked(sf::Vector2i& mousePosition) {

        if (_camerasView.getViewport().contains(static_cast<float>(mousePosition.x) / SCREEN_WIDTH, static_cast<float>(mousePosition.y) / SCREEN_HEIGHT))
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
        for (int i = 0; i<3; i++)
        {
            if(!_camerasOn.at(i)){
                this->_data->window.draw(_buttons.at(i));
            }
            if(_camerasOn.at(i) && !_isAddingCamera){
                this->_data->window.draw(_removeButtons.at(i));
            }
            this->_data->window.draw(_camerasLabels.at(i));
        } 
        
        this->_data->window.draw(_buttons.at(3));
            
        for (int i = 3; i < 6; i++)
        {
            if (_camerasOn.at(i - 3)) {
                this->_data->window.draw(_camerasLabels.at(i));
                this->_data->window.draw(_camerasLabels.at(i + 3));
            }
        }
    }

    void CamerasView::UpdateCarsLabel(int whichLabel){
        ++_numberOfCars[whichLabel];
        this->_camerasLabels.at(whichLabel+2).setString("Cars passed: "+std::to_string(_numberOfCars[whichLabel]));
    }
    
    void CamerasView::UpdateTrucksLabel(int whichLabel){
        ++_numberOfTrucks[whichLabel];
        this->_camerasLabels.at(whichLabel+5).setString("Trucks passed: "+std::to_string(_numberOfTrucks[whichLabel]));
    }
    void CamerasView::UpdateIsSimulating(bool isSimulating){
        if(!isSimulating){
            this->InitializeVehiclesCounters();
        }
    }
    void CamerasView::UpdateIsAddingCamera(bool isAddingCamera, int whichCamera, int row, int col) {
        this->_isAddingCamera = isAddingCamera;
        if (!isAddingCamera) {
            
            this->_camerasOn.at(whichCamera - 1) = true;
            
            this->_buttons.at(whichCamera - 1).setBackground(this->_data->assets.GetTexture("Button"));
            _camerasLabels.at(whichCamera - 1).setString("Camera " + std::to_string(whichCamera) + ": Row: "+ std::to_string(col+1)+" Col: "+std::to_string(row+1));
        }
        else {
            this->_buttons.at(whichCamera - 1).setBackground(this->_data->assets.GetTexture("Button_pressed"));
        }
    }
    void CamerasView::UpdateIsDeletingCamera(int whichCamera) {
        this->_camerasOn.at(whichCamera - 1) = false;
        this->_buttons.at(whichCamera - 1).setText("Add camera " + std::to_string(whichCamera));
        this->_buttons.at(whichCamera - 1).setBackground(this->_data->assets.GetTexture("Button"));
        _camerasLabels.at(whichCamera - 1).setString("Camera " + std::to_string(whichCamera) + ": Disabled");
    }

    
    void CamerasView::HandleInput(){
        for (Button& button : this->_buttons){
            if (button.isClicked(sf::Mouse::Left, this->_data->window, this->_camerasView)){
                if (button.getText() == "Start simulation" || button.getText() == "Stop simulation"  ) {
                    if (this->_buttons.at(3).isPressed) {
                        this->_buttons.at(3).setBackground(this->_data->assets.GetTexture("Button"));
                        button.setText("Start simulation");
                    }
                    else{
                        this->_buttons.at(3).setBackground(this->_data->assets.GetTexture("Button_pressed"));

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
                button.isPressed = !button.isPressed;

            }
        }
    
        for (Button& button : this->_removeButtons){
            if (button.isClicked(sf::Mouse::Left, this->_data->window, this->_camerasView)){
                
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
