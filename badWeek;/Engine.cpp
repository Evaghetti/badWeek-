#include "Engine.h"

#include "Rand.h"

Engine::Engine(const std::string& nome, int largura, int altura)
	: window(sf::VideoMode(largura, altura), nome),
	  playState(&window)
{
	run();
}

void Engine::run() {
	while (playState.works()) {
		playState.handleInput();
		playState.update();
		playState.draw();
	}
}
