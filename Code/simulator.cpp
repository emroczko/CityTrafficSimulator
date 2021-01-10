/**
 * simulator.cpp
 * Implementation of Simulator class.
 */

#include "simulator.hpp"
#include "splash_state.hpp"

namespace zpr{

    /**
     * Parametrized constructor of Simulator class.
     * @param width - Width of the window_.
     * @param height - Height of the window_.
     * @param title - Title of the window_.
     */
    Simulator::Simulator(int width, int height, std::string title){
    
        data_->window_.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
        data_->machine_.addState(StateRef(new SplashState(this->data_)));
        this->run();
    }
    /**
     * Method resposible for application loop, executes drawing, updating and handling input.
     */
    void Simulator::run(){
    
        float new_time, frame_time, interpolation;
        float current_time = this-> clock_.getElapsedTime().asSeconds();
        float accumulator = 0.0f;
    
        while(this->data_->window_.isOpen()){
            this->data_->machine_.processStateChanges();
        
            new_time = this-> clock_.getElapsedTime().asSeconds();
            frame_time = new_time - current_time;
        
            if (frame_time > 0.25f){
                frame_time = 0.25f;
            }
            current_time = new_time;
            accumulator += frame_time;
        
            while (accumulator >= dt_)
            {
                this->data_->machine_.getActiveState()->handleInput();
                this->data_->machine_.getActiveState()->update(dt_);
                accumulator -= dt_;
            }
            interpolation = accumulator / dt_;
            this->data_->machine_.getActiveState()->draw(interpolation);
        }
    }

}
