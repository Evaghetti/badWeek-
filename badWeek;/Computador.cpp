#include "Computador.h"
#include "Manager.h"

#include <iostream>

Computador::Computador(const sf::Vector2f& position, const sf::Vector2f& scale)
	: sprite(*TextureManager::carregar("Imagens/Computer.png")),
	menu("1) Codar\n2) Navegar Na internet.\n3) Mandar projeto pro seu chefe para avaliação.\n", {0.f, 0.f, 0.f, 0.f}, true)
{
	sprite.setPosition(position);
	sprite.setScale(scale);

	menu.setRect({ sprite.getPosition() + sf::Vector2f(38.f, 28.f), sf::Vector2f(768.f * scale.x, 518.f * scale.y) });
	menu.setFontSize(30 * scale.x);
	menu.setFontColor(sf::Color::Black);
}

void Computador::draw(sf::RenderTarget& target) {
	target.draw(sprite);
	menu.draw(target);
}

void Computador::handleInput(const char letra) {
	std::cout << "Você digitou: " << letra << std::endl;
	menu.update();
}
