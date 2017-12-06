#include "GameState.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <vector>

class Engine {
	public:
		Engine(const std::string& nome, int largura, int altura);
		void run();
	private:
		sf::RenderWindow window;
		std::vector<GameState*> gameStates;
		GameState* gameState;
};

