#include "FrameWork/Manager.h"
#include "Computador.h"

#include <sstream>
#include <fstream>

Computador::Computador(const sf::Vector2f& position, const sf::Vector2f& scale)
	: principal("1) Codar\n2) Navegar Na internet.\n3) Mandar projeto pro\nseu chefe para avaliação.\n", sf::FloatRect(), true),
	  codigo("", sf::FloatRect())
{
	texturaSprite = TextureManager::carregar("Imagens/Computer.png");
	texturaNavegador = TextureManager::carregar("Imagens/navegador.png");
	bufferSomTeclado = SoundBufferManager::carregar("Sounds/clicando.wav");

	sprite = sf::Sprite(*texturaSprite);
	navegador = sf::Sprite(*texturaNavegador);

	somTeclado = sf::Sound(*bufferSomTeclado);
	somTeclado.setVolume(100.f);
	screenOffset = position + sf::Vector2f(30.f * scale.x, 30.f * scale.y);
	screenSize = sf::Vector2f(796.f * scale.x, 470.f * scale.y);

	sprite.setPosition(position);
	sprite.setScale(scale);

	navegador.setPosition(screenOffset);
	navegador.setScale(scale);
	
	principal.setRect({screenOffset, screenSize});
	principal.setFontSize(30.0f * scale.x);
	principal.setFontColor(sf::Color::Black);
	principal.update();

	codigo.setParams(principal);

	botaoLigar = sf::FloatRect(position.x + 832.f * scale.x, position.y + 510.f * scale.y, 12.f * scale.x, 12.f * scale.y);
	
	paginaAtual = PRINCIPAL;
	ligado = true;
	terminouCode = false;
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
		somTeclado.play();
		switch (paginaAtual) {
			case PRINCIPAL:
				terminouCode = false;
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
				else if (letra == '3')
					paginaAtual = MANDAR_PROJETO;
			break;
			case CODAR:
				if (!codigo.done()) {
					for (int i = 0; i < 3; i++)
						codigo.update();
				}
				else {
					codigo.setMensagem("");
					paginaAtual = PRINCIPAL;
					terminouCode = true;
				}
				break;
			case NAVEGAR:
				paginaAtual = PRINCIPAL;
				break;
			case MANDAR_PROJETO:
				paginaAtual = MANDAR_PROJETO;
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

bool Computador::terminouProgramar() {
	if (terminouCode) {
		terminouCode = false;
		return true;
	}
	return false;
}