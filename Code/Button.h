#pragma once
#include "SFML/Graphics.hpp"

class Button : public sf::Drawable
{
public:
	Button();
	Button(sf::Vector2f position);
	Button(sf::Vector2f position, sf::Vector2f size);
	Button(sf::Vector2f position, sf::Vector2f size, sf::String text);
	Button(sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Texture background);
	bool isClicked(sf::Mouse::Button mouse_button, sf::RenderWindow& window);
	void setPosition(sf::Vector2f position);
	void setText(sf::String text);
	void setBackground(sf::Texture &background);
	void setSize(sf::Vector2f size);
	void setFillcolor(sf::Color color);
	void setFont(sf::Font &font);
	void setFontSize(unsigned int font_size);
	void setTextColor(sf::Color color);
	sf::String getText();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	sf::RectangleShape _rectangle;
	sf::Text _text;
private:
	
	
};

