#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Computador {
	public:
		Computador(const sf::Vector2f& position, const sf::Vector2f& scale = { 1.0f, 1.0f });
		void draw(sf::RenderTarget& target);
		void handleInput();
	private:
		sf::Sprite sprite;
};

