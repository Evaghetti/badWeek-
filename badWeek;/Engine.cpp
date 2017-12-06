#include "Engine.h"
#include "PlayState.h"
#include "Judge.h"

Engine::Engine(const std::string& nome, int largura, int altura)
	: window(sf::VideoMode(largura, altura), nome)
	  
{
	gameStates.push_back(new Judge(&window));
	gameStates.push_back(new PlayState(&window));
	gameState = gameStates.front();
	run();
}

void Engine::run() {
	while (!gameStates.empty()) {
		while (gameState->works()) {
			gameState->handleInput();
			gameState->update();
			gameState->draw();
		}

		gameStates.erase(gameStates.begin());
		if (!gameStates.empty())
			gameState = gameStates.front();
	}
}
