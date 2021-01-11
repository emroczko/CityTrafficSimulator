#include "init_create_state_helper.hpp"

namespace zpr {
    
    /**
     * Method returning size of grid depending from which button was clicked.
     * @param button - Clicked button.
     * @return - Grid size.
     */
    int InitCreateStateHelper::getGridSizeFromButton(Button button)
    {
        std::string button_text = button.getText();
        std::string text_to_change = button_text.substr(0, 2);
        return changeTextToInt(button_text);
    }
    /**
     * Method returning size of grid from button text
     * @param text_to_change - Text which should be converted to int
     * @return - Grid size.
     */
    int InitCreateStateHelper::changeTextToInt(std::string text_to_change)
    {
        return std::stoi(text_to_change, nullptr);
    }
}
