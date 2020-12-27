#include "Button.h"
#include "Definitions.h"
#include <iostream>
namespace ZPR {
	Button::Button() {}

	Button::Button(sf::Vector2f position)
	{
		this->_rectangle.setPosition(position);
		this->_text.setPosition(position);
	}

	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Texture& background)
	{
		this->_rectangle.setPosition(sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2));
		this->_rectangle.setSize(size);
		this->_rectangle.setTexture(&background);
	}

	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font& font, unsigned int fontSize, sf::Color textColor, sf::Texture& background)
	{
		this->_rectangle.setPosition(sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2));
		this->_rectangle.setSize(size);
		this->_rectangle.setTexture(&background);

		this->_text.setString(text);
		this->_text.setFont(font);
		this->_text.setCharacterSize(fontSize);
		this->_text.setFillColor(textColor);
		this->_text.setPosition(sf::Vector2f(this->_rectangle.getPosition().x + this->_rectangle.getGlobalBounds().width / 2 - this->_text.getGlobalBounds().width / 2,
			this->_rectangle.getPosition().y + this->_rectangle.getGlobalBounds().height / 2 - this->_text.getGlobalBounds().height));
	}

	bool Button::isClicked(sf::Mouse::Button mouseButton, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(mouseButton))
		{
			sf::IntRect tempRect(this->_rectangle.getPosition().x, this->_rectangle.getPosition().y, this->_rectangle.getGlobalBounds().width, this->_rectangle.getGlobalBounds().height);
			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}

	bool Button::isClicked(sf::Mouse::Button mouseButton, sf::RenderWindow& window, sf::View view)
	{
		if (sf::Mouse::isButtonPressed(mouseButton))
		{
			sf::IntRect tempRect(this->_rectangle.getPosition().x, this->_rectangle.getPosition().y, this->_rectangle.getGlobalBounds().width, this->_rectangle.getGlobalBounds().height);
			sf::Vector2f position = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
			sf::Vector2i posint = static_cast<sf::Vector2i>(position);
			if (tempRect.contains(posint))
			{
				return true;
			}
		}
		return false;
	}

	void Button::setPosition(sf::Vector2f position)
	{
		this->_rectangle.setPosition(position);
		this->_text.setPosition(position);
	}

	void Button::setText(sf::String text)
	{
		this->_text.setString(text);
	}

	void Button::setBackground(sf::Texture& background)
	{
		this->_rectangle.setTexture(&background);
	}

	void Button::setSize(sf::Vector2f size)
	{
		this->_rectangle.setSize(size);
	}

	void Button::setFillcolor(sf::Color color)
	{
		this->_rectangle.setFillColor(color);
	}

	void Button::setFont(sf::Font& font)
	{
		this->_text.setFont(font);
	}

	void Button::setFontSize(unsigned int font_size)
	{
		this->_text.setCharacterSize(font_size);
	}

	void Button::setTextColor(sf::Color color)
	{
		this->_text.setFillColor(color);
	}

	void Button::ButtonQuickMaker(sf::String text, sf::Vector2f size, sf::Color fillColor, sf::Font& font, unsigned int fontSize, sf::Color textColor)
	{
		this->_text.setString(text);
		this->_rectangle.setSize(size);
		this->_rectangle.setFillColor(fillColor);
		this->_text.setFont(font);
		this->_text.setCharacterSize(fontSize);
		this->_text.setFillColor(textColor);
	}

	sf::String Button::getText()
	{
		return this->_text.getString();
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->_rectangle, states);
		target.draw(this->_text, states);
	}
}
