/**
 * button.cpp
 * Implementation of Button class.
 */

#include "button.hpp"
#include "../definitions.hpp"
#include <iostream>
namespace zpr {

    /**
     * Default constructor of Button class
     */
	Button::Button() {
        this->isPressed_ = false;
    }

    /**
     * Parametrized constructor of Button class.
     * @param text - Text which should be on the button.
     */
    Button::Button(sf::String text) : isPressed_(false)
    {
        this->text_.setString(text);
    }
    /**
     * Parametrized constructor of Button class.
     * @param position - Position of where button should be placed.
     */
	Button::Button(sf::Vector2f position) : isPressed_(false)
	{
		this->rectangle_.setPosition(position);
		this->text_.setPosition(position);
	}
    /**
     * Parametrized constructor of Button class.
     * @param position - Position of where button should be placed.
     * @param size - Size of button that should be placed.
     * @param background - Background of button that should be placed.
     */
	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Texture& background)
	{
		this->rectangle_.setPosition(sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2));
		this->rectangle_.setSize(size);
		this->rectangle_.setTexture(&background);
		this->isPressed_ = false;
	}
 
    /**
     * Parametrized constructor of Button class.
     * @param position - Position of where button should be placed.
     * @param size - Size of button that should be placed.
     * @param text - Text which should be on the button.
     * @param font - Font of text on the button.
     * @param font_size - Size of font on the button.
     * @param text_color - Color of font on the button.
     * @param background - Background of button that should be placed.
     */
	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font& font, unsigned int font_size, sf::Color text_color, sf::Texture& background)
	{
		this->rectangle_.setPosition(sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2));
		this->rectangle_.setSize(size);
		this->rectangle_.setTexture(&background);

		this->text_.setString(text);
		this->text_.setFont(font);
		this->text_.setCharacterSize(font_size);
		this->text_.setFillColor(text_color);
		this->text_.setPosition(sf::Vector2f(this->rectangle_.getPosition().x + this->rectangle_.getGlobalBounds().width / 2 - this->text_.getGlobalBounds().width / 2,
			this->rectangle_.getPosition().y + this->rectangle_.getGlobalBounds().height / 2 - this->text_.getGlobalBounds().height));
		this->isPressed_ = false;
	}
    /**
     * Method returning infromation if button was pressed depending from where mouse was clicked in the whole window.
     * @param mouse_button - Button of mouse which clicked.
     * @param window - Window where button was clicked and where is the button we are checking.
     * @return - Return true if button was clicked or false otherwise.
     */
	bool Button::isClicked(sf::Mouse::Button mouse_button, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(mouse_button))
		{
			sf::IntRect tempRect(this->rectangle_.getPosition().x, this->rectangle_.getPosition().y, this->rectangle_.getGlobalBounds().width, this->rectangle_.getGlobalBounds().height);
			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}
    /**
     * Method returning information if button was pressed depending from where mouse was clicked in the certain sf::View class.
     * @param mouse_button - Button of mouse which clicked.
     * @param window - Window where button was clicked and where is the button we are checking.
     * @param view - View where button was clicked and where is the button we are checking.
     */
	bool Button::isClicked(sf::Mouse::Button mouse_button, sf::RenderWindow& window, sf::View view)
	{
		if (sf::Mouse::isButtonPressed(mouse_button))
		{
			sf::IntRect tempRect(this->rectangle_.getPosition().x, this->rectangle_.getPosition().y, this->rectangle_.getGlobalBounds().width, this->rectangle_.getGlobalBounds().height);
			sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
			sf::Vector2i posint = static_cast<sf::Vector2i>(position);
			if (tempRect.contains(posint))
			{
				return true;
			}
		}
		return false;
	}
    /**
     * Method responsible for setting position of button.
     * @param position - Position where the button should be placed.
     */
	void Button::setPosition(sf::Vector2f position)
	{
		this->rectangle_.setPosition(position);
		this->text_.setPosition(position);
	}

    /**
     * Method responsible for setting the text displayed on the button.
     * @param text - String which should be put on the button.
     */
	void Button::setText(sf::String text)
	{
		this->text_.setString(text);
	}

    /**
     * Method responsible for background texture of the button.
     * @param background - Background which should be set.
     */
	void Button::setBackground(sf::Texture& background)
	{
		this->rectangle_.setTexture(&background);
	}

    /**
     * Method responsible for setting the size of the button.
     * @param size - Size of the button.
     */
	void Button::setSize(sf::Vector2f size)
	{
		this->rectangle_.setSize(size);
	}

    /**
     * Method responsible for setting the color of the button.
     * @param color - Fill color which shoud be set on the button.
     */
	void Button::setFillcolor(sf::Color color)
	{
		this->rectangle_.setFillColor(color);
	}

    /**
     * Method responsible for setting the font of the button text.
     * @param font - Font which should button text have.
     */
	void Button::setFont(sf::Font& font)
	{
		this->text_.setFont(font);
	}

/**
 * Method responsible for setting the color of the button.
 * @param font_size - Size of the font on the button.
 */
	/*Ustawia rozmier czcionki uzywanej do wyswietlania tekstu na przycisku*/
	void Button::setFontSize(unsigned int font_size)
	{
		this->text_.setCharacterSize(font_size);
	}

/**
 * Method responsible for setting the color of the button.
 * @param color - Fill color which shoud be set on the button.
 */
	/*Ustawia kolor tekstu na przycisku*/
	void Button::setTextColor(sf::Color color)
	{
		this->text_.setFillColor(color);
	}

    /**
     * Method returning an information wheter button was pressed.
     * @return - True when button was pressed, false otherwise.
     */
	bool& Button::GetIsPressed()
	{
		return this->isPressed_;
	}

    /**
     * Method returning text which is on the button.
     * @return - Text on the button.
     */
	sf::String Button::getText()
	{
		return this->text_.getString();
	}

    /**
     * Method returning position of the button.
     * @return - Position of the button.
     */
    sf::Vector2f Button::getPosition(){
        return this->text_.getPosition();
    }

    /**
     * Method responsible for drawing the button.
     * @param target - Target where button should be drawn.
     * @param states - RenderStates
     */
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->rectangle_, states);
		target.draw(this->text_, states);
	}
}
