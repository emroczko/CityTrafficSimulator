/**
 * viewport_calculator.cpp
 * Implementation of ViewportCalculator class.
 */

#include "viewport_calculator.hpp"

namespace zpr {


    /**
     * Method responsible for calculating viewport of cameras view.
     * @return - Calculated viewport.
     */
    sf::FloatRect ViewportCalculator::calculateCamerasViewport()
    {
        float rect_width = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
        float rect_left = 0.f;
        return sf::FloatRect(rect_left, 0.f, rect_width, 1.f);
    }

    /**
     * Method responsible for calculating viewport of map view.
     * @return - Calculated viewport.
     */
    sf::FloatRect ViewportCalculator::calculateMapViewport()
    {
        float rect_width = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
        float rect_left = (1.f - rect_width)/2;
        return sf::FloatRect(rect_left, 0.f, rect_width, 1.f);
    }

    /**
     * Method responsible for calculating viewport of tools view.
     * @return - Calculated viewport.
     */
    sf::FloatRect ViewportCalculator::calculateToolsViewport()
    {
        float rect_width = (1.f - (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) / 2;
        float rect_left = rect_width + (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
        return sf::FloatRect(rect_left, 0.f, rect_width, 1.f);
    }

}
