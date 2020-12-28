#pragma once
#include "SFML/Graphics.hpp"

namespace ZPR {
	class Button : public sf::Drawable
	{
	public:
		Button();
		Button(sf::Vector2f position);
		Button(sf::Vector2f position, sf::Vector2f size, sf::Texture& background);
		Button(sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font& font, unsigned int fontSize, sf::Color textColor, sf::Texture& background);

		bool isClicked(sf::Mouse::Button mouseButton, sf::RenderWindow& window);
		bool isClicked(sf::Mouse::Button mouseButton, sf::RenderWindow& window, sf::View view);
		void setPosition(sf::Vector2f position);
		void setBackground(sf::Texture& background);

		void setText(sf::String text);
		void setSize(sf::Vector2f size);
		void setFillcolor(sf::Color color);
		void setFont(sf::Font& font);
		void setFontSize(unsigned int fontSize);
		void setTextColor(sf::Color color);
		bool& GetIsPressed();
		
		sf::String getText();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool isPressed;
	private:
		sf::RectangleShape _rectangle;
		sf::Text _text;
		
	};
}
