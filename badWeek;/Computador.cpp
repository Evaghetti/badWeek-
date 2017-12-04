#include "Computador.h"
#include "Manager.h"

Computador::Computador(const sf::Vector2f& position, const sf::Vector2f& scale)
	: sprite(*TextureManager::carregar("Imagens/Computer.png")) 
{
	sprite.setPosition(position);
	sprite.setScale(scale);
}

void Computador::draw(sf::RenderTarget& target) {
	target.draw(sprite);
}

void Computador::handleInput() {

}
