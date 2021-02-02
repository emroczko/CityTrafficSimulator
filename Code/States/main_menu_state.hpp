/**
 * main_menu_state.hpp
 * Header of MainMenuState class.
 */
#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "../simulator.hpp"
#include "../components/button.hpp"
#include "../components/cell.hpp"
#include "../helpers/file_finder.hpp"



namespace zpr{

/**
 Klasa odpowiadająca za menu główne programu
 */
    class MainMenuState : public State{
        
    public:
        MainMenuState (SimulatorDataRef data);
        void init();
        void handleInput();
        void update(float dt);
        void draw(float dt);
        unsigned long getButtonsAmount();
        void loadDemo();
        
    private:
        void initializeButtons();
        SimulatorDataRef data_;
        sf::Sprite background_;
        std::vector<Button> buttons_;
        std::vector<Cell> cells_;
        int gridSize_;
        FileFinder fileFinder_;
        Cell tempCell_;
    };

}
