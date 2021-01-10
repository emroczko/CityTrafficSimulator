#include "tools_view.hpp"
#include "save_state.hpp"

namespace zpr {
	ToolsView::ToolsView(SimulatorDataRef data) : data_(data)
	{
        this->isSimulating_ = false;
        this->isAddingCameras_ = false;
		this->toolsView_ = sf::View(sf::FloatRect(0.f, 0.f, (float)((SCREEN_WIDTH - SCREEN_HEIGHT) / 2), (float)(SCREEN_HEIGHT)));
		this->toolsView_.setViewport(this->calculateViewPort());
		this->background_.setPosition(0, 0);
		this->background_.setSize(this->toolsView_.getSize());
		this->background_.setFillColor(sf::Color(80, 80, 80));
        
        this->data_->assets_.loadTexture("Button", BUTTON_FILEPATH);
        this->data_->assets_.loadTexture("Button_pressed", BUTTON_PRESSED_FILEPATH);
        this->data_->assets_.loadFont("Text font", TEXT_FONT_FILEPATH);
        
        this->buttonInitializer();
        
	}
    void ToolsView::buttonInitializer(){
        sf::Vector2f button_size(150, 66);
        int font_size = 30;
        this->buttons_.push_back(Button(sf::Vector2f(toolsView_.getSize().x/2, 100), button_size, "Create new street",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
   
        this->buttons_.push_back(Button(sf::Vector2f(toolsView_.getSize().x/2, 250), button_size, "Delete streets",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
        
        this->buttons_.push_back(Button(sf::Vector2f(toolsView_.getSize().x/2, 800), button_size, "Save to file",
            this->data_->assets_.getFont("Text font"), font_size, sf::Color::White, this->data_->assets_.getTexture("Button")));
    }
	sf::FloatRect ToolsView::calculateViewPort()
	{
        float rect_width = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
        float rect_left = rect_width + (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
        return sf::FloatRect(rect_left, 0.f, rect_width, 1.f);
	}

	void ToolsView::draw()
	{
		this->data_->window_.setView(this->toolsView_);
		this->data_->window_.draw(this->background_);
		this->drawButtons();
	}

    bool ToolsView::isClicked(sf::Vector2i mouse_position){
    
        if(toolsView_.getViewport().contains(static_cast<float>(mouse_position.x)/SCREEN_WIDTH, static_cast<float>(mouse_position.y)/SCREEN_HEIGHT))
            return true;
        else
            return false;
    }
    void ToolsView::handleInput(){
        for (Button& button : this->buttons_){
                if (isSimulating_ || isAddingCameras_){
                    button.isPressed_ = false;
                    button.setBackground(this->data_->assets_.getTexture("Button"));
                }
            if (button.isClicked(sf::Mouse::Left, this->data_->window_, this->toolsView_)){
                
                if (button.getText() == "Create new street" && !isSimulating_) {
                    if (this->buttons_.at(1).isPressed_) {
                        this->buttons_.at(1).setBackground(this->data_->assets_.getTexture("Button"));
                    }
                    this->buttons_.at(1).isPressed_ = false;
                    this->notifyIsDrawingRoad();
                }

                if (button.getText() == "Delete streets" && !isSimulating_) {
                    if (this->buttons_.at(0).isPressed_) {
                        this->buttons_.at(0).setBackground(this->data_->assets_.getTexture("Button"));
                    }
                    this->buttons_.at(0).isPressed_ = false;
                    this->notifyIsDeletingRoad();
                }
                if (button.getText() == "Save to file" && !isSimulating_) {
                    if (this->buttons_.at(0).isPressed_) {
                        this->buttons_.at(0).setBackground(this->data_->assets_.getTexture("Button"));
                    }
                    this->buttons_.at(0).isPressed_ = false;
                    this->notifySave();
                }

                //Tu doda³em ¿eby siê zmienia³ bg przycisku jak siê kliknie i odkliknie //
                button.isPressed_ = !button.isPressed_;
                if (button.isPressed_) {
                    button.setBackground(this->data_->assets_.getTexture("Button_pressed"));
                }
                else {
                    button.setBackground(this->data_->assets_.getTexture("Button"));
                }
               
            }
        }
    }
    void ToolsView::updateIsSimulating(bool is_simulating){
        this->isSimulating_ = is_simulating;
        this->handleInput();
    }
    void ToolsView::updateIsAddingCamera(bool isAddingCamera, int whichCamera){
        this->isAddingCameras_ = isAddingCamera;
        this->handleInput();
    }

	void ToolsView::drawButtons()
	{
        if (!this->isSimulating_ || !this->isAddingCameras_){
            for (Button button: buttons_)
            {
                this->data_->window_.draw(button);
            }
        }
	}
    sf::View ToolsView::getView()
    {
        return this->toolsView_;
    }

}
