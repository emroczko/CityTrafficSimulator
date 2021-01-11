#pragma once

#include "button.hpp"


namespace zpr{

    class InitCreateStateHelper{
    public:
        int getGridSizeFromButton(Button);
        int changeTextToInt(std::string);
    };
}
