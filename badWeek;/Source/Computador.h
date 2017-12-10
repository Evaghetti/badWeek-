#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "FrameWork/GUI/Writer.h"
#include "FrameWork/Random.h"

enum Pagina {
	CODAR,
	NAVEGAR,
	MANDAR_PROJETO,
	PRINCIPAL
};

class Computador {
	public:
		Computador(const sf::Vector2f& position, const sf::Vector2f& scale = { 1.0f, 1.0f });
		void draw(sf::RenderTarget& target);
		void handleInput(const char letra);
		void handleMouse(const sf::Vector2f& mousePosition);

		Pagina getPaginaAtual() const;
		bool taLigado() const;
		bool terminouProgramar();
	private:
		void lerCodigo(const std::string& caminho);
	private:
		std::shared_ptr<sf::Texture> texturaSprite, texturaNavegador;
		std::shared_ptr<sf::SoundBuffer> bufferSomTeclado;

		sf::Sprite sprite, navegador;
		sf::FloatRect botaoLigar;
		sf::Vector2f screenOffset, screenSize;
		sf::Sound somTeclado;

		Random random;
		Writer principal, codigo;
		Pagina paginaAtual;

		bool ligado, terminouCode;
};

