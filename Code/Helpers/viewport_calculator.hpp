/**
 * viewport_calculator.hpp
 * Header of ViewportCalculator class.
 */

#pragma once
#include "SFML/Graphics.hpp"
#include "../definitions.hpp"

namespace zpr {

    /**
     * Class responsible for calculating viewport of views.
     */
    class ViewportCalculator{
    public:
        sf::FloatRect calculateCamerasViewport();
        sf::FloatRect calculateMapViewport();
        sf::FloatRect calculateToolsViewport();
    };
}
