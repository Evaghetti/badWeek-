#pragma once
#include "Widget.h"
#include "../Writer.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

class Button : public Widget {
	public:
		Button(const sf::Vector2f& position, const sf::Vector2f& tamanho, const std::string& text = {"Você digitou nada."});
	
		void draw(sf::RenderTarget& target) override;
	
		void handleInput() override;
		void handleMouse(const sf::Vector2f& mousePos) override;

		bool foiUsado() const override;
	private:
		sf::RectangleShape buttonBox;
		Writer buttonText;
};