#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "simulator.hpp"
#include "button.hpp"
#include "cell.hpp"
#include "file_finder.hpp"



namespace ZPR{

/**
 Klasa odpowiadająca za menu główne programu
 */
    class MainMenuState : public State{
        
    public:
        MainMenuState (SimulatorDataRef data);
        void Init();
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
        unsigned long GetButtonsAmount();
        void LoadDemo();
        
    private:
        SimulatorDataRef _data;
        sf::Sprite _background;
        std::vector<Button> _buttons;
        std::vector<Cell> _cells;
        int _gridSize;
        FileFinder _fileFinder;
        Cell _tempCell;
    };

}
