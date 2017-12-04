#include "Engine.h"

#include <iostream>
#include <exception>

Engine::Engine(const std::string& nome, int largura, int altura)
	: window(sf::VideoMode(largura, altura), nome),
	  playState(&window)
{
	try {
		run();
	}
	catch (std::exception& e) {
		std::cout << "Teste: " << e.what();
	}
}

void Engine::run() {
	while (playState.works()) {
		playState.handleInput();
		playState.update();
		playState.draw();
	}
}
