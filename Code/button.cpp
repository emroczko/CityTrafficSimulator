#include "button.hpp"
#include "definitions.hpp"
#include <iostream>
namespace ZPR {
	Button::Button() { this->isPressed = false; }

	Button::Button(sf::Vector2f position) : isPressed(false)
	{
		this->_rectangle.setPosition(position);
		this->_text.setPosition(position);
	}

	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Texture& background)
	{
		this->_rectangle.setPosition(sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2));
		this->_rectangle.setSize(size);
		this->_rectangle.setTexture(&background);
		this->isPressed = false;
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
		this->isPressed = false;
	}
	/*Zwraca informacjê czy przycisk zosta³ klikniêty w zale¿noœci od miejsca klikniêcia myszki na ekranie*/
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
	/*Zwraca informacjê czy przycisk zosta³ klikniêty w zale¿noœci od miejsca klikniêcia myszki na segmencie ekranu (View)*/
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
	/*Ustawia pozycje przyciku*/
	void Button::setPosition(sf::Vector2f position)
	{
		this->_rectangle.setPosition(position);
		this->_text.setPosition(position);
	}
	/*Ustawia tekst wyswietlany na przycisku*/
	void Button::setText(sf::String text)
	{
		this->_text.setString(text);
	}
	/*Ustawia teksturê z jak¹ bêdzie wyœwietlany przycisk*/
	void Button::setBackground(sf::Texture& background)
	{
		this->_rectangle.setTexture(&background);
	}
	/*Ustawia rozmier przycisku*/
	void Button::setSize(sf::Vector2f size)
	{
		this->_rectangle.setSize(size);
	}
	/*ustawia kolor wype³nienia przycisku*/
	void Button::setFillcolor(sf::Color color)
	{
		this->_rectangle.setFillColor(color);
	}
	/*Ustawia czcionkê z jak¹ bêdzie wyœwietlany tekst przycisku*/
	void Button::setFont(sf::Font& font)
	{
		this->_text.setFont(font);
	}
	/*Ustawia rozmier czcionki uzywanej do wyswietlania tekstu na przycisku*/
	void Button::setFontSize(unsigned int font_size)
	{
		this->_text.setCharacterSize(font_size);
	}
	/*Ustawia kolor tekstu na przycisku*/
	void Button::setTextColor(sf::Color color)
	{
		this->_text.setFillColor(color);
	}
	/*Zwraca informacjê o tym czy przycisk jest wciœniêty*/
	bool& Button::GetIsPressed()
	{
		return this->isPressed;
	}
	/*Zwraca tekst który jest wyswietlany na przycisku*/
	sf::String Button::getText()
	{
		return this->_text.getString();
	}
    sf::Vector2f Button::getPosition(){
        return this->_text.getPosition();
    }
	/*Rysuje przycisk*/
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->_rectangle, states);
		target.draw(this->_text, states);
	}
}
