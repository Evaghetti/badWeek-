#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <memory>
#include <string>
#include <vector>

class SmoothWrite {
	public:
		SmoothWrite(const std::string& mensagem, const sf::FloatRect& caixa);
		
		void draw(sf::RenderTarget& target);
		void update();
	private:
		void ler(const std::string& mensagem);
		void formatar();
		bool checarDentro(const sf::FloatRect& outro) const;
	private:
		std::vector<std::string> palavras;
		std::shared_ptr<sf::Font> fonte;
		std::string palavraAtual;

		sf::Text texto;
		sf::FloatRect caixa;
};

