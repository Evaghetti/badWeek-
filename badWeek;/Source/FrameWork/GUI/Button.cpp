#include "Button.h"

#include <SFML/Window/Mouse.hpp>

Button::Button(const sf::Vector2f& position, const sf::Vector2f& tamanho, 
			   const std::string& text) 
			  : Widget(position),
				buttonBox(tamanho),
				buttonText(text, {position, tamanho}, true, "Fontes/UI.ttf")
{
	buttonBox.setPosition(position);
	buttonBox.setFillColor(sf::Color::Cyan);
	buttonText.update();
}

void Button::handleInput() {

}

void Button::handleMouse(const sf::Vector2f& mousePos) {
	if (buttonBox.getGlobalBounds().contains(mousePos)) {
		buttonBox.setFillColor(sf::Color::Blue);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			usado = true;
	}
	else {
		buttonBox.setFillColor(sf::Color::Cyan);
		usado = false;
	}
}

void Button::draw(sf::RenderTarget& target) {
	target.draw(buttonBox);
	buttonText.draw(target);
}

bool Button::foiUsado() const {
	return usado;
}