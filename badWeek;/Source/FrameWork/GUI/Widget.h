#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class Widget {
	public:
		Widget(const sf::Vector2f& position);

		virtual void draw(sf::RenderTarget& target) = 0;

		virtual void handleInput() = 0;
		virtual void handleMouse(const sf::Vector2f& mousePos) = 0;
		virtual bool foiUsado() const = 0;
	protected:
		sf::Vector2f position;
		bool usado;
};