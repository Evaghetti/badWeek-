#include "Computador.h"
#include "Manager.h"

#include <sstream>
#include <fstream>

Computador::Computador(const sf::Vector2f& position, const sf::Vector2f& scale)
	: sprite(*TextureManager::carregar("Imagens/Computer.png")),
	  navegador(*TextureManager::carregar("Imagens/Navegador.png")),
	  principal("1) Codar\n2) Navegar Na internet.\n3) Mandar projeto pro seu chefe para avaliação.\n", sf::FloatRect(), true),
	  codigo("", sf::FloatRect())
{
	screenOffset = position + sf::Vector2f(47.f * scale.x, 32.f * scale.y);
	screenSize = sf::Vector2f(763.f * scale.x, 508.f * scale.y);

	sprite.setPosition(position);
	sprite.setScale(scale);

	navegador.setPosition(screenOffset);
	navegador.setScale(scale);
	
	principal.setRect({screenOffset, screenSize});
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
			case NAVEGAR:
				target.draw(navegador);
				break;
		}
	}
		
}

void Computador::handleInput(const char letra) {
	if (ligado) {
		switch (paginaAtual) {
			case PRINCIPAL:
				if (letra == '1') {
					std::stringstream caminho;
					caminho << "Codigos/" << random.range(1, 5) << ".cpp";
					try {
						lerCodigo(caminho.str());
						paginaAtual = CODAR;
					}
					catch (...) {
						paginaAtual = PRINCIPAL;
					}
				}
				else if (letra == '2') 
					paginaAtual = NAVEGAR;
			break;
			case CODAR:
				if (!codigo.done()) {
					for (int i = 0; i < 3; i++)
						codigo.update();
				}
				else {
					codigo.setMensagem("");
					paginaAtual = PRINCIPAL;
				}
				break;
			case NAVEGAR:
				paginaAtual = PRINCIPAL;
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

Pagina Computador::getPaginaAtual() const {
	return paginaAtual;
}

bool Computador::taLigado() const {
	return ligado;
}