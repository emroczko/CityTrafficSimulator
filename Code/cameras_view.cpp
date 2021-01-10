#include "cameras_view.hpp"
#include <iostream>


namespace zpr {

    CamerasView::CamerasView(SimulatorDataRef data) : data_(data), isSimulating_(false), isAddingCamera_(false)
    {
        this->camerasView_ = sf::View(sf::FloatRect(0.f, 0.f, (float)((SCREEN_WIDTH - SCREEN_HEIGHT) / 2), (float)(SCREEN_HEIGHT)));
        this->camerasView_.setViewport(this->calculateViewPort());
        this->background_.setPosition(0, 0);
        this->background_.setSize(this->camerasView_.getSize());
        this->background_.setFillColor(sf::Color(80, 80, 80));
        

        this->addButtons();
        this->camerasLabels("Camera 1: Disabled", 50);
        this->camerasLabels("Camera 2: Disabled", 280);
        this->camerasLabels("Camera 3: Disabled", 510);
        this->camerasLabels("Cars passed: 0", 100);
        this->camerasLabels("Cars passed: 0", 330);
        this->camerasLabels("Cars passed: 0", 560);
        this->camerasLabels("Trucks passed: 0", 150);
        this->camerasLabels("Trucks passed: 0", 380);
        this->camerasLabels("Trucks passed: 0", 610);
        

        for (int i = 0; i < 3; i++) {
            this->camerasOn_.push_back(false);
        }
        
        this->initializeVehiclesCounters();
    }

    void CamerasView::initializeVehiclesCounters(){
        for (int i = 0; i < 3; i++) {

            numberOfCars_[i] = 0;
            numberOfTrucks_[i] = 0;

            this->camerasLabels_.at(i + 3).setString("Cars passed: " + std::to_string(this->numberOfCars_[i]));
            this->camerasLabels_.at(i + 6).setString("Trucks passed: " + std::to_string(this->numberOfTrucks_[i]));

        }
    }
    void CamerasView::addButtons() {
        sf::Vector2f buttonSize(150, 66);
        int fontSize = 30;
        for (int i = 1; i < 4; i++) {
            this->buttons_.push_back(Button(sf::Vector2f(2*camerasView_.getSize().x / 8, 230 * i), buttonSize, "Add camera " + std::to_string(i),
                this->data_->assets_.getFont("Text font"), fontSize, sf::Color::White, this->data_->assets_.getTexture("Button")));
            this->removeButtons_.push_back(Button(sf::Vector2f(6*camerasView_.getSize().x / 8, 230 * i), buttonSize, "Remove camera " + std::to_string(i),
                this->data_->assets_.getFont("Text font"), fontSize, sf::Color::White, this->data_->assets_.getTexture("Button")));
        }
        

        this->buttons_.push_back(Button(sf::Vector2f(camerasView_.getSize().x / 2, 900), buttonSize, "Start simulation",
            this->data_->assets_.getFont("Text font"), fontSize, sf::Color::White, this->data_->assets_.getTexture("Button")));
    }
    void CamerasView::camerasLabels(std::string text, int yPosition) {
        sf::Text tempLabel;
        tempLabel.setFont(this->data_->assets_.getFont("Text font"));
        tempLabel.setCharacterSize(30);
        tempLabel.setString(text);
        tempLabel.setPosition(camerasView_.getSize().x / 6, yPosition);
        this->camerasLabels_.push_back(tempLabel);

    }
    sf::FloatRect CamerasView::calculateViewPort()
    {
        float rectWidth = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
        float rectLeft = 0.f;
        return sf::FloatRect(rectLeft, 0.f, rectWidth, 1.f);
    }

    bool CamerasView::isClicked(sf::Vector2i& mousePosition) {

        if (camerasView_.getViewport().contains(static_cast<float>(mousePosition.x) / SCREEN_WIDTH, static_cast<float>(mousePosition.y) / SCREEN_HEIGHT))
            return true;
        else
            return false;
    }
    void CamerasView::draw()
    {
        this->data_->window_.setView(this->camerasView_);
        this->data_->window_.draw(this->background_);
        this->drawButtons();
    }
    void CamerasView::drawButtons()
    {
        for (int i = 0; i<3; i++)
        {
            if(!camerasOn_.at(i)){
                this->data_->window_.draw(buttons_.at(i));
            }
            if(camerasOn_.at(i) && !isAddingCamera_){
                this->data_->window_.draw(removeButtons_.at(i));
            }
            this->data_->window_.draw(camerasLabels_.at(i));
        } 
        
        this->data_->window_.draw(buttons_.at(3));
            
        for (int i = 3; i < 6; i++)
        {
            if (camerasOn_.at(i - 3)) {
                this->data_->window_.draw(camerasLabels_.at(i));
                this->data_->window_.draw(camerasLabels_.at(i + 3));
            }
        }
    }

    void CamerasView::updateCarsLabel(int whichLabel){
        ++numberOfCars_[whichLabel-1];
        this->camerasLabels_.at(whichLabel+2).setString("Cars passed: "+std::to_string(numberOfCars_[whichLabel-1]));
    }
    
    void CamerasView::updateTrucksLabel(int whichLabel){
        ++numberOfTrucks_[whichLabel-1];
        this->camerasLabels_.at(whichLabel+5).setString("Trucks passed: "+std::to_string(numberOfTrucks_[whichLabel-1]));
    }
    void CamerasView::updateIsSimulating(bool isSimulating){
        if(!isSimulating){
            this->initializeVehiclesCounters();
        }
    }

    void CamerasView::updateIsAddingCamera(bool isAddingCamera, int whichCamera) {
        this->isAddingCamera_ = isAddingCamera;
        if (!isAddingCamera) {
            this->buttons_.at(whichCamera - 1).setBackground(this->data_->assets_.getTexture("Button"));
        }
        else {
            this->buttons_.at(whichCamera - 1).setBackground(this->data_->assets_.getTexture("Button_pressed"));
        }
    }

    void CamerasView::updateCameraAdded(int whichCamera, int row, int col)
    {
        this->camerasOn_.at(whichCamera - 1) = true;
        camerasLabels_.at(whichCamera - 1).setString("Camera " + std::to_string(whichCamera) + ": Row: " + std::to_string(col + 1) + " Col: " + std::to_string(row + 1));
    }
    void CamerasView::updateIsDeletingCamera(int whichCamera) {
        this->camerasOn_.at(whichCamera - 1) = false;
        this->buttons_.at(whichCamera - 1).setText("Add camera " + std::to_string(whichCamera));
        this->buttons_.at(whichCamera - 1).setBackground(this->data_->assets_.getTexture("Button"));
        camerasLabels_.at(whichCamera - 1).setString("Camera " + std::to_string(whichCamera) + ": Disabled");
    }

    
    void CamerasView::handleInput(){
        for (Button& button : this->buttons_){
            if (button.isClicked(sf::Mouse::Left, this->data_->window_, this->camerasView_)){
                if (button.getText() == "Start simulation" || button.getText() == "Stop simulation"  ) {
                    if (this->buttons_.at(3).isPressed_) {
                        this->buttons_.at(3).setBackground(this->data_->assets_.getTexture("Button"));
                        button.setText("Start simulation");
                    }
                    else{
                        this->buttons_.at(3).setBackground(this->data_->assets_.getTexture("Button_pressed"));

                        button.setText("Stop simulation");
                    }
                    this->notifyIsSimulating();
                }
                if (button.getText() == "Add camera 1") {
                    this->notifyIsAddingCamera(1);
                    this->numberOfCars_[0] = 0;
                    this->numberOfTrucks_[0] = 0;
                    this->camerasLabels_.at(3).setString("Cars passed: " + std::to_string(numberOfCars_[0]));
                    this->camerasLabels_.at(6).setString("Trucks passed: " + std::to_string(numberOfTrucks_[0]));
                }
                if (button.getText() == "Add camera 2") {
                    this->notifyIsAddingCamera(2);
                    this->numberOfCars_[1] = 0;
                    this->numberOfTrucks_[1] = 0;
                    this->camerasLabels_.at(4).setString("Cars passed: " + std::to_string(numberOfCars_[1]));
                    this->camerasLabels_.at(7).setString("Trucks passed: " + std::to_string(numberOfTrucks_[1]));
                    
                }
                if (button.getText() == "Add camera 3") {
                    this->notifyIsAddingCamera(3);
                    this->numberOfCars_[2] = 0;
                    this->numberOfTrucks_[2] = 0;
                    this->camerasLabels_.at(5).setString("Cars passed: " + std::to_string(numberOfCars_[2]));
                    this->camerasLabels_.at(8).setString("Trucks passed: " + std::to_string(numberOfTrucks_[2]));
                }
                button.isPressed_ = !button.isPressed_;
            }
        }
    
        for (Button& button : this->removeButtons_){
            if (button.isClicked(sf::Mouse::Left, this->data_->window_, this->camerasView_)){
                
                if (button.getText() == "Remove camera 1") {
                    //this->ButtonsHandler(button, "Camera 1: ", 0, 0);
                    this->notifyIsDeletingCamera(1);

                }
                if (button.getText() == "Remove camera 2") {
                    // this->ButtonsHandler(button, "Camera 2: ", 1, 1);
                    this->notifyIsDeletingCamera(2);
                }
                if (button.getText() == "Remove camera 3") {
                    //this->ButtonsHandler(button, "Camera 3: ", 2, 2);
                    this->notifyIsDeletingCamera(3);
                }
                button.isPressed_ = !button.isPressed_;

            }
        }
       
    }
}
