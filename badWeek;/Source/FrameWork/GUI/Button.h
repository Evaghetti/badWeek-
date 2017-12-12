#pragma once
#include "Widget.h"
#include "Writer.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

class Button : public Widget {
	public:
		Button(const sf::Vector2f& position, const sf::Vector2f& tamanho, const std::string& text = {"Você digitou nada."});
	
		void draw(sf::RenderTarget& target) override;
		void update() override;
	
		void handleInput() override;
		void handleMouse(const sf::Vector2f& mousePos) override;

		bool foiUsado() const override;
	private:
		sf::RectangleShape buttonBox;
		Writer buttonText;

		const sf::Color normal = sf::Color(125, 125, 125, 255);
		const sf::Color selecionado = sf::Color(75, 75, 75, 255);
};