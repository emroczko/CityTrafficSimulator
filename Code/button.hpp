/**
 * button.hpp
 * Header of Button class.
 */

#pragma once
#include "SFML/Graphics.hpp"

namespace zpr {
    
    /**
     * Class responsible for being a button in every state of application.
     */
	class Button : public sf::Drawable
	{
	public:
		Button();
		Button(sf::Vector2f position);
		Button(sf::Vector2f position, sf::Vector2f size, sf::Texture& background);
		Button(sf::Vector2f position, sf::Vector2f size, sf::String text, sf::Font& font, unsigned int font_size, sf::Color text_color, sf::Texture& background);

		bool isClicked(sf::Mouse::Button mouse_button, sf::RenderWindow& window);
		bool isClicked(sf::Mouse::Button mouse_button, sf::RenderWindow& window, sf::View view);
		void setPosition(sf::Vector2f position);
		void setBackground(sf::Texture& background);

		void setText(sf::String text);
		void setSize(sf::Vector2f size);
		void setFillcolor(sf::Color color);
		void setFont(sf::Font& font);
		void setFontSize(unsigned int font_size);
		void setTextColor(sf::Color color);
		bool& GetIsPressed();
		
		sf::String getText();
        sf::Vector2f getPosition();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		bool isPressed_;
	private:
		sf::RectangleShape rectangle_;
		sf::Text text_;
		
	};
}
