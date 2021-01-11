/**
 * init_create_state_helper.hpp
 * Header of InitCreateStateHelper class.
 */


#pragma once

#include "button.hpp"


namespace zpr{

    /**
     * Class responsible for doing some actions for InitCreateState window.
     */
    class InitCreateStateHelper{
    public:
        int getGridSizeFromButton(Button);
        int changeTextToInt(std::string);
    };
}
