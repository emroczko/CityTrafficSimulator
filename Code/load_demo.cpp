#include "load_demo.hpp"
#include "creator_state.hpp"
#include "main_menu_state.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace ZPR {
    LoadDemo::LoadDemo(SimulatorDataRef data) : _data(data){}
    /*Metoda inicjujπca wszystkie elementy potrzebne do poprawnego dzia≥ania obiektu*/

    void LoadDemo::LoadFromFile(){
        std::ifstream myfile;
        int howMany = 0;
        
        myfile.open ("Demo.txt");
        if (myfile.is_open()){
        myfile >> _gridSize;
        
        while (myfile >> _tempCell)
        {
            _cells.emplace_back(_tempCell);
            howMany++;
        }
        myfile.close();
        }
        else{
            
        }
        std::cout<<howMany<<std::endl;
        this->_data->machine.AddState(StateRef(new CreatorState(this->_data, this->_gridSize, this->_cells)), false);
    }
    
}

