/**
 * tools_view.cpp
 * Implementation of ToolsView class.
 */

#include "tools_view.hpp"
#include "../states/save_state.hpp"
#include "../states/init_create_state.hpp"

namespace zpr {

    /**
     * Parametrized constructor of ToolsView class.
     * @param data - Struct containing data of current application. (eg. window, assets).
     */
	ToolsView::ToolsView(SimulatorDataRef data) : data_(data)
	{
        this->isSimulating_ = false;
        this->isAddingCameras_ = false;
		this->toolsView_ = sf::View(sf::FloatRect(0.f, 0.f, (float)((SCREEN_WIDTH - SCREEN_HEIGHT) / 2), (float)(SCREEN_HEIGHT)));
		this->toolsView_.setViewport(this->viewportCalculator_.calculateToolsViewport());
		this->background_.setPosition(0, 0);
		this->background_.setSize(this->toolsView_.getSize());
		this->background_.setFillColor(sf::Color(80, 80, 80));
        
        this->data_->assets_.loadTexture("Button", BUTTON_FILEPATH);
        this->data_->assets_.loadTexture("Button_pressed", BUTTON_PRESSED_FILEPATH);
        this->data_->assets_.loadFont("Text font", TEXT_FONT_FILEPATH);
        
        this->buttonInitializer();
	}

    /**
     * Method which initializes every button in the window.
     */
    void ToolsView::buttonInitializer(){
        sf::Vector2f button_size(210, 66);
        int font_size = 30;
        this->buttons_.push_back(Button(sf::Vector2f(toolsView_.getSize().x/2, 100), button_size, "Create new street",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
   
        this->buttons_.push_back(Button(sf::Vector2f(toolsView_.getSize().x/2, 250), button_size, "Delete streets",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(toolsView_.getSize().x/2, 800), button_size, "Save to file",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(toolsView_.getSize().x/2, 900), button_size, "Back",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
    }


    /**
     * Method which draws elements of tools view in the window.
     */
	void ToolsView::draw()
	{
		this->data_->window_.setView(this->toolsView_);
		this->data_->window_.draw(this->background_);
        if (!isSimulating_) {
            this->drawButtons();
        }
	}

    /**
     * Method checking if clicked position is inside tools view.
     * @param mouse_position - Current mouse position.
     * @return - Returns true if position is inside tools view, false otherwise.
     */
    bool ToolsView::isClicked(sf::Vector2i mouse_position){
    
        if(toolsView_.getViewport().contains(static_cast<float>(mouse_position.x)/SCREEN_WIDTH, static_cast<float>(mouse_position.y)/SCREEN_HEIGHT))
            return true;
        else
            return false;
    }

    /**
     Method which handles user input in the current view.
     */
    void ToolsView::handleInput(){
        for (Button& button : this->buttons_){
            if (!isSimulating_ && !isAddingCameras_) {
                if (button.isClicked(sf::Mouse::Left, this->data_->window_, this->toolsView_)) {

                    if (button.getText() == "Create new street" && !isSimulating_) {
                        this->resetButtons(1, 2);
                        this->notifyIsDrawingRoad();
                    }

                    if (button.getText() == "Delete streets" && !isSimulating_) {
                        this->resetButtons(0, 2);
                        this->notifyIsDeletingRoad();
                    }
                    if (button.getText() == "Save to file" && !isSimulating_) {
                        this->resetButtons(0, 1);
                        this->notifySave();
                    }
                    if (button.getText() == "Back") {
                        this->data_->machine_.addState(StateRef(new InitCreateState(this->data_)), false);
                    }
                    button.isPressed_ = !button.isPressed_;
                    if (button.isPressed_) {
                        button.setBackground(this->data_->assets_.getTexture("Button_pressed"));
                    }
                    else {
                        button.setBackground(this->data_->assets_.getTexture("Button"));
                    }
                }
            }
            else {
                button.isPressed_ = false;
                button.setBackground(this->data_->assets_.getTexture("Button"));
            }
        }
    }

    /**
     * Inherited method which updates ToolsView when simulation is taking place.
     * @param is_simulating - True when simulation starts, false otherwise.
     */
    void ToolsView::updateIsSimulating(bool is_simulating){
        this->isSimulating_ = is_simulating;
        this->handleInput();
    }

    /**
     * Inherited method which updates ToolsView when user is adding a camera.
     * @param is_adding_camera - True when user is adding a camera, false otherwise.
     * @param which_camera - Being added camera number.
     */
    void ToolsView::updateIsAddingCamera(bool is_adding_camera, int which_camera){
        this->isAddingCameras_ = is_adding_camera;
        this->handleInput();
    }
    
    /**
     * Method which draws buttons on the screen.
     */
	void ToolsView::drawButtons()
	{
        if (!this->isSimulating_ || !this->isAddingCameras_){
            for (Button button: buttons_)
            {
                this->data_->window_.draw(button);
            }
        }
	}

    /**
     * Method which resets buttons to default state (not clicked)
     * @param button_number_1 - number of button to reset
     * @param button_number_2 - number of second button to reset
     */
    void ToolsView::resetButtons(int button_number_1, int button_number_2)
    {
        this->buttons_.at(button_number_1).setBackground(this->data_->assets_.getTexture("Button"));
        this->buttons_.at(button_number_2).setBackground(this->data_->assets_.getTexture("Button"));
        this->buttons_.at(button_number_1).isPressed_ = false;
        this->buttons_.at(button_number_2).isPressed_ = false;
    }

    /**
     * Method which returns current view.
     * @return - Current sf::View. 
     */
    sf::View ToolsView::getView()
    {
        return this->toolsView_;
    }

}
