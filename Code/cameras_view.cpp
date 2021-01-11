/**
 * cameras_view.cpp
 * Implementation of CamerasView class.
 */

#include "cameras_view.hpp"
#include <iostream>

namespace zpr {

    /**
     * Parametrized constructor of CamerasView class.
     * @param data - Struct containing data of current application. (eg. window, assets).
     */
    CamerasView::CamerasView(SimulatorDataRef data) : data_(data), isSimulating_(false), isAddingCamera_(false)
    {
        this->camerasView_ = sf::View(sf::FloatRect(0.f, 0.f, (float)((SCREEN_WIDTH - SCREEN_HEIGHT) / 2), (float)(SCREEN_HEIGHT)));
        this->camerasView_.setViewport(this->calculateViewPort());
        this->background_.setPosition(0, 0);
        this->background_.setSize(this->camerasView_.getSize());
        this->background_.setFillColor(sf::Color(80, 80, 80));
        this->addButtons();
        this->camerasInitialization();
        
        for (int i = 0; i < 3; i++) {
            this->camerasOn_.push_back(false);
        }
        this->initializeVehiclesCounters();
    }

    /**
     * Method which initializes cameras labels.
     */
    void CamerasView::camerasInitialization(){
        
        this->camerasLabels_.push_back(this->createLabel("Camera 1: Disabled", 50));
        this->camerasLabels_.push_back(this->createLabel("Camera 2: Disabled", 280));
        this->camerasLabels_.push_back(this->createLabel("Camera 3: Disabled", 510));
        this->camerasLabels_.push_back(this->createLabel("Cars passed: 0", 100));
        this->camerasLabels_.push_back(this->createLabel("Cars passed: 0", 330));
        this->camerasLabels_.push_back(this->createLabel("Cars passed: 0", 560));
        this->camerasLabels_.push_back(this->createLabel("Trucks passed: 0", 150));
        this->camerasLabels_.push_back(this->createLabel("Trucks passed: 0", 380));
        this->camerasLabels_.push_back(this->createLabel("Trucks passed: 0", 610));
        this->startSimulationLabel_ = this->createLabel("", 815);

    }

    /**
     * Method which initializes vehicles counters.
     */
    void CamerasView::initializeVehiclesCounters(){
        for (int i = 0; i < 3; i++) {

            numberOfCars_[i] = 0;
            numberOfTrucks_[i] = 0;

            this->camerasLabels_.at(i + 3).setString("Cars passed: " + std::to_string(this->numberOfCars_[i]));
            this->camerasLabels_.at(i + 6).setString("Trucks passed: " + std::to_string(this->numberOfTrucks_[i]));

        }
    }

    /**
     * Method which adds buttons to the view.
     */
    void CamerasView::addButtons() {
        sf::Vector2f button_size(160, 66);
        sf::Vector2f remove_buttons_size(180, 66);
        sf::Vector2f start_simulation_button_size(200, 66);
        int font_size = 30;
        for (int i = 1; i < 4; i++) {
            this->buttons_.push_back(Button(sf::Vector2f(2*camerasView_.getSize().x / 8, 230 * i), button_size, "Add camera " + std::to_string(i),
                this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
            this->removeButtons_.push_back(Button(sf::Vector2f(6*camerasView_.getSize().x / 8 - 5, 230 * i), remove_buttons_size, "Remove camera " + std::to_string(i),
                this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        }
        this->buttons_.push_back(Button(sf::Vector2f(camerasView_.getSize().x / 2, 900), start_simulation_button_size, "Start simulation",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
    }

    /**
     * Method which creates text labels in the view.
     * @param text - Text displayed in the label.
     * @param y_position - Y position of the label.
     * @return - Returns label as a sf::Text object.
     */
    sf::Text CamerasView::createLabel(std::string text, int y_position) {
        sf::Text tempLabel;
        tempLabel.setFont(this->data_->assets_.getFont("Text font"));
        tempLabel.setCharacterSize(30);
        tempLabel.setString(text);
        tempLabel.setPosition(camerasView_.getSize().x / 6, y_position);
        return tempLabel;
    }

    /**
     * Method responsible for calculating viewport of this view.
     * @return - Calculated viewport.
     */
    sf::FloatRect CamerasView::calculateViewPort()
    {
        float rectWidth = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
        float rectLeft = 0.f;
        return sf::FloatRect(rectLeft, 0.f, rectWidth, 1.f);
    }

    /**
     * Method checking if clicked position is inside tools view.
     * @param mouse_position - Current mouse position.
     * @return - Returns true if position is inside tools view, false otherwise.
     */
    bool CamerasView::isClicked(sf::Vector2i& mouse_position) {

        if (camerasView_.getViewport().contains(static_cast<float>(mouse_position.x) / SCREEN_WIDTH, static_cast<float>(mouse_position.y) / SCREEN_HEIGHT))
            return true;
        else
            return false;
    }

    /**
     * Method which draws elements of tools view in the window.
     */
    void CamerasView::draw()
    {
        this->data_->window_.setView(this->camerasView_);
        this->data_->window_.draw(this->background_);
        this->drawButtons();
        this->drawLabels();
    }

    /**
     * Method which draws buttons in the view.
     */
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
        } 
        this->data_->window_.draw(buttons_.at(3));        
    }

    /**
     * Method which draws labels in the view.
     */
    void CamerasView::drawLabels() {
        for (int i = 0; i < 3; i++)
        {
            if (camerasOn_.at(i)) {
                this->data_->window_.draw(camerasLabels_.at(i+3));
                this->data_->window_.draw(camerasLabels_.at(i + 6));
            }
            this->data_->window_.draw(camerasLabels_.at(i));
            this->data_->window_.draw(startSimulationLabel_);
        }
    }

    /**
     * Method which checks if starting road is connected to roads drawn by user.
     * @return - True when user drawn road is connected to start road.
     */
    bool CamerasView::startingRoadConnected()
    {
        if (this->cells_.size()>0 && this->cells_.at(sqrt(this->cells_.size())*STARTING_CELL_COL).containsRoad_) 
            return true;
        else
            return false;
    }

    /**
     * Method which resets cameras' counters of vehicles.
     * @param which_camera - Reseted counter camera number.
     */
    void CamerasView::resetCameraCounter(int which_camera)
    {
        this->numberOfCars_[which_camera-1] = 0;
        this->numberOfTrucks_[which_camera-1] = 0;
        this->camerasLabels_.at(which_camera+2).setString("Cars passed: " + std::to_string(numberOfCars_[which_camera-1]));
        this->camerasLabels_.at(which_camera +5).setString("Trucks passed: " + std::to_string(numberOfTrucks_[which_camera-1]));
    }

    /**
     * Method responsible for updating car labels.
     * @param which_label - Label to update.
     */
    void CamerasView::updateCarsLabel(int which_label){
        ++numberOfCars_[which_label-1];
        this->camerasLabels_.at(which_label+2).setString("Cars passed: "+std::to_string(numberOfCars_[which_label-1]));
    }
    
    /**
     * Method responsible for updating trucks labels.
     * @param which_label - Label to update.
     */
    void CamerasView::updateTrucksLabel(int which_label){
        ++numberOfTrucks_[which_label-1];
        this->camerasLabels_.at(which_label+5).setString("Trucks passed: "+std::to_string(numberOfTrucks_[which_label-1]));
    }

    /**
     * Method responsible for updating this view when simulation is taking place.
     * @param is_simulating - True when simulation starts, false when it ends.
     */
    void CamerasView::updateIsSimulating(bool is_simulating){
        if(!is_simulating){
            this->initializeVehiclesCounters();
        }
    }
    
    /**
     * Method responsible for updating this view when user is adding a camera.
     * @param is_adding_camera - True when user is adding camera, false otherwise.
     * @param which_camera - Being added camera's number.
     */
    void CamerasView::updateIsAddingCamera(bool is_adding_camera, int which_camera) {
        this->isAddingCamera_ = is_adding_camera;
        if (!is_adding_camera) {
            this->buttons_.at(which_camera - 1).setBackground(this->data_->assets_.getTexture("Button"));
        }
        else {
            this->buttons_.at(which_camera - 1).setBackground(this->data_->assets_.getTexture("Button_pressed"));
        }
    }

    /**
     * Method responsible for updating this view when user added a camera.
     * @param which_camera - Added camera's number.
     * @param row - Row where camera was added.
     * @param col - Column where camera was added.
     */
    void CamerasView::updateCameraAdded(int which_camera, int row, int col)
    {
        this->camerasOn_.at(which_camera - 1) = true;
        camerasLabels_.at(which_camera - 1).setString("Camera " + std::to_string(which_camera) + ": Row: " + std::to_string(col + 1) + " Col: " + std::to_string(row + 1));
    }

    /**
     * Method responsible for update vector of cells for this view.
     * @param cells - Vector of new cells.
     */
    void CamerasView::updateCells(std::vector<Cell> cells)
    {
        this->cells_ = cells;
    }

    /**
     * Method responsible for updating this view when user is deleting camera.
     * @param which_camera - Camera which user deletes.
     */
    void CamerasView::updateIsDeletingCamera(int which_camera) {
        this->camerasOn_.at(which_camera - 1) = false;
        this->buttons_.at(which_camera - 1).setText("Add camera " + std::to_string(which_camera));
        this->buttons_.at(which_camera - 1).setBackground(this->data_->assets_.getTexture("Button"));
        camerasLabels_.at(which_camera - 1).setString("Camera " + std::to_string(which_camera) + ": Disabled");
    }

    /**
     * Method which handles user input in the current view.
     */
    void CamerasView::handleInput(){
        for (Button& button : this->buttons_){
            if (button.isClicked(sf::Mouse::Left, this->data_->window_, this->camerasView_)){
                if (button.getText() == "Start simulation" || button.getText() == "Stop simulation"  ) {
                    if (this->buttons_.at(3).getText() == "Stop simulation") {
                        this->buttons_.at(3).setBackground(this->data_->assets_.getTexture("Button"));
                        button.setText("Start simulation");
                        this->notifyIsSimulating();
                    }
                    else if(this->startingRoadConnected()){
                        this->buttons_.at(3).setBackground(this->data_->assets_.getTexture("Button_pressed"));
                        button.setText("Stop simulation");
                        this->startSimulationLabel_.setString("");
                        this->notifyIsSimulating();
                    }
                    else {
                        this->startSimulationLabel_.setString("Entry road not connected");
                    }
                }
                if (button.getText() == "Add camera 1") {
                    this->notifyIsAddingCamera(1);
                    this->resetCameraCounter(1);
                }
                if (button.getText() == "Add camera 2") {
                    this->notifyIsAddingCamera(2);
                    this->resetCameraCounter(2);
                    
                }
                if (button.getText() == "Add camera 3") {
                    this->notifyIsAddingCamera(3);
                    this->resetCameraCounter(3);
                }
                button.isPressed_ = !button.isPressed_;
            }
        }
    
        for (Button& button : this->removeButtons_){
            if (button.isClicked(sf::Mouse::Left, this->data_->window_, this->camerasView_)){
                
                if (button.getText() == "Remove camera 1") {
                    this->notifyIsDeletingCamera(1);

                }
                if (button.getText() == "Remove camera 2") {
                    this->notifyIsDeletingCamera(2);
                }
                if (button.getText() == "Remove camera 3") {
                    this->notifyIsDeletingCamera(3);
                }
                button.isPressed_ = !button.isPressed_;

            }
        }
       
    }
}
