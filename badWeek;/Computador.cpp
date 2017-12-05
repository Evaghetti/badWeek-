#include "Computador.h"
#include "Manager.h"

#include <sstream>
#include <fstream>

Computador::Computador(const sf::Vector2f& position, const sf::Vector2f& scale)
	: sprite(*TextureManager::carregar("Imagens/Computer.png")),
	  principal("1) Codar\n2) Navegar Na internet.\n3) Mandar projeto pro seu chefe para avaliação.\n", sf::FloatRect(), true),
	  codigo(".", sf::FloatRect())
{
	sprite.setPosition(position);
	sprite.setScale(scale);

	principal.setRect({ position + sf::Vector2f(50.f * scale.x, 30.f * scale.y), sf::Vector2f(768.f * scale.x, 518.f * scale.y) });
	principal.setFontSize(30.0f * scale.x);
	principal.setFontColor(sf::Color::Black);
	principal.update();

	codigo.setParams(principal);

	botaoLigar = sf::FloatRect(position.x + 756.f * scale.x, position.y + 545.f * scale.y, 44.f * scale.x, 43.f * scale.y);
	
	paginaAtual = PRINCIPAL;
	ligado = false;
}

void Computador::draw(sf::RenderTarget& target) {
	target.draw(sprite);
	if (ligado) {
		switch (paginaAtual) {
			case PRINCIPAL:
				principal.draw(target);
				break;
			case CODAR:
				codigo.draw(target);
				break;
		}
	}
		
}

void Computador::handleInput(const char letra) {
	if (ligado) {
		switch (paginaAtual) {
			case PRINCIPAL:
				if (letra == '1') {
					lerCodigo("Codigos/4.cpp");
					paginaAtual = CODAR;
				}
			break;
			case CODAR:
				codigo.update();
				break;
		}
	}
}

void Computador::handleMouse(const sf::Vector2f& mousePosition) {
	if (botaoLigar.contains(mousePosition)) {
		ligado = !ligado;
		paginaAtual = PRINCIPAL;
	}
}

void Computador::lerCodigo(const std::string& caminho) {
	std::ifstream arquivo(caminho);
	std::stringstream sb;
	std::string buffer;

	if (!arquivo.good())
		throw std::runtime_error("Erro ao abrir arquivo");
	
	while (std::getline(arquivo, buffer, '\n')) 
		sb << buffer << '\n';

	codigo.scaleToFit(sb.str(), .85f);
	codigo.setMensagem(sb.str());
}