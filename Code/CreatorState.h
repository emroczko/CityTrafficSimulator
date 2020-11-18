#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Simulator.h"
#include "Button.h"

#include <vector>

#include "Button.h"


namespace ZPR{
    
    class CreatorState: public State{
    
    public:
        CreatorState (SimulatorDataRef data, int gridSize);
        
        void Init();
        
        void HandleInput();
        void Update(float dt);
        void Draw(float dt);
    private:
        void drawGrid();
        void GenerateGrid();
        SimulatorDataRef _data;
        int _gridSize;
        sf::View _manageCamerasView, _creatorView, _creatorToolsView;
        sf::RectangleShape _backgroundColor;
        std::vector<Button> _toolsButtons;
        std::vector<sf::RectangleShape> _gridLines;
        sf::Sprite _grid;
        sf::Sprite _backgroundTexture;
        std::vector<Button> _buttons;
    };
}
