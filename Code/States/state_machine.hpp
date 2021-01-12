/**
 * state_machine.hpp
 * Header of StateMachine class.
 */

#pragma once

#include <memory>
#include <stack>
#include "state.hpp"

namespace zpr {

    /**
     * Assigning StateRef as a name to std::unique_ptr<State> type.
     */
    typedef std::unique_ptr<State> StateRef;

    /**
     * Class responsible for handling application states.
     */
    class StateMachine{
    public:
        StateMachine(){}
        ~StateMachine(){}
        void addState( StateRef new_state, bool is_replacing = true);
        void removeState();
        void processStateChanges();
        bool& getIsAdding();
        StateRef &getActiveState();
    private:
        std::stack<StateRef> states_;
        StateRef newState_;
        bool isRemoving_;
        bool isAdding_;
        bool isReplacing_;
    };
}

