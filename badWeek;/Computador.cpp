#include "Computador.h"
#include "Manager.h"

#include <iostream>

Computador::Computador(const sf::Vector2f& position, const sf::Vector2f& scale)
	: sprite(*TextureManager::carregar("Imagens/Computer.png")),
	  menu("1) Codar\n2) Navegar Na internet.\n3) Mandar projeto pro seu chefe para avaliação.\n", {0.f, 0.f, 0.f, 0.f}, true)
{
	sprite.setPosition(position);
	sprite.setScale(scale);

	menu.setRect({ position + sf::Vector2f(50.f * scale.x, 30.f * scale.y), sf::Vector2f(768.f * scale.x, 518.f * scale.y) });
	menu.setFontSize(30.0f * scale.x);
	menu.setFontColor(sf::Color::Black);

	botao = sf::FloatRect(position.x + 756.f * scale.x, position.y + 545.f * scale.y, 44.f * scale.x, 43.f * scale.y);

	ligado = false;
}

void Computador::draw(sf::RenderTarget& target) {
	target.draw(sprite);
	if (ligado)
		menu.draw(target);
}

void Computador::handleInput(const char letra) {
	if (ligado) {
		std::cout << "Você digitou: " << letra << std::endl;
		menu.update();
	}
}

void Computador::handleMouse(const sf::Vector2f& mousePosition) {
	if (botao.contains(mousePosition))
		ligado = !ligado;
}
