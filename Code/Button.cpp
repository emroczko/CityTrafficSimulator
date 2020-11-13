#include "Button.h"
#include "Definitions.h"
#include <iostream>

Button::Button(){}

Button::Button(sf::Vector2f position)
{
	this->_rectangle.setPosition(position);
	this->_text.setPosition(position);
}

Button::Button(sf::Vector2f position, sf::Vector2f size)
{
	this->_rectangle.setPosition(position);
	this->_text.setPosition(position);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::String text)
{
	this->_rectangle.setPosition(position);
	this->_text.setPosition(position);
}

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Texture background)
{
	this->_rectangle.setPosition(position);
	this->_text.setPosition(position);
}

bool Button::isClicked(sf::Mouse::Button mouse_button, sf::RenderWindow& window) 
{
	if (sf::Mouse::isButtonPressed(mouse_button)) 
	{
		sf::IntRect tempRect(this->_rectangle.getPosition().x, this->_rectangle.getPosition().y, this->_rectangle.getGlobalBounds().width, this->_rectangle.getGlobalBounds().height);
		if (tempRect.contains(sf::Mouse::getPosition(window))) 
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

void Button::setBackground(sf::Texture &background)
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

void Button::setFont(sf::Font &font)
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

sf::String Button::getText()
{
	return this->_text.getString();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->_rectangle, states);
	target.draw(this->_text, states);
}

