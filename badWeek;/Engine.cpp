#include "Engine.h"

#include "Rand.h"

Engine::Engine(const std::string& nome, int largura, int altura)
	: window(sf::VideoMode(largura, altura), nome),
	  judge(&window)
{
	run();
}

void Engine::run() {
	while (judge.works()) {
		judge.handleInput();
		judge.update();
		judge.draw();
	}
}
