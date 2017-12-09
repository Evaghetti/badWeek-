#include "FrameWork/GameState.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include <string>
#include <vector>

class Engine {
	public:
		Engine(const std::string& nome, int largura, int altura);
	private:
		void run();
	private:
		sf::RenderWindow window;
		std::vector<std::unique_ptr<GameState>> gameStates;
};

