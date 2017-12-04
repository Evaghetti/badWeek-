#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Writer.h"

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
	private:
		sf::Sprite sprite;
		sf::FloatRect botao;
		
		Writer menu;
		Pagina paginaAtual;

		bool ligado = false;
};

