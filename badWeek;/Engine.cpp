#include "Engine.h"

#include "Rand.h"

Engine::Engine(const std::string& nome, int largura, int altura)
	: window(sf::VideoMode(largura, altura), nome),
	  judge(&window)
{
	Player player;
	player.quantCodigos = 14;
	player.felicidade = -20.f;
	player.sono = 121.f;

	judge.julgar(player);
	run();
}

void Engine::run() {
	while (judge.works()) {
		judge.handleInput();
		judge.update();
		judge.draw();
	}
}
