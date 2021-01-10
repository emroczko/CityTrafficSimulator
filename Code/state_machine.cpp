/**
 * state_machine.cpp
 * Implementation of StateMachine class.
 */

#include "state_machine.hpp"

namespace zpr
{
    /**
     * Method responsible for setting the adding state status.
     * @param new_state - New state of application.
     * @param is_replacing - Information about is new state replacing previous. ,
     */
    void StateMachine::addState(StateRef new_state, bool is_replacing){
        this->isAdding_ = true;
        this->isReplacing_ = is_replacing;
        this->newState_ = std::move(new_state);
    }
    /**
     * Methods responsible for setting the deleting state status.
     */
    void StateMachine::removeState(){
        this -> isRemoving_ = true;
    }
    /**
     * Method responsible for handling states (adding, removing)
     */
    void StateMachine::processStateChanges(){
        if (this-> isRemoving_ && !this-> states_.empty()){
            this->states_.pop();
        
            if (!this-> states_.empty())
                this->states_.top()-> resume();
            
            this-> isRemoving_ = false;
        }
        if(this ->isAdding_)
        {
            if(!this -> states_.empty())
            {
                if(this-> isReplacing_)
                    this->states_.pop();
                
                else
                    this-> states_.top()->pause();
                
            }
            this-> states_.push(std::move(this-> newState_));
            this-> states_.top() -> init();
            this-> isAdding_ = false;
        }
    }
    /**
     * Method responsible for getting active state.
     * @return - Returns active state.
     */
    StateRef &StateMachine::getActiveState()
    {
        return this-> states_.top();
    }
    /**
     * Method which returns true if state is being added or false otherwise.
     * @return - Bool value, true if state is being added or false otherwise
     */
    bool& StateMachine::getIsAdding() {
        return this->isAdding_;
    }

    
}
