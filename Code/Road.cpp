#include "Road.h"

namespace ZPR {

    sf::Vector2i Road::GetPosition()
    {
        return sf::Vector2i(this->_row, this->_column);
    }

}
