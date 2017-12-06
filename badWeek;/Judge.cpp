#include "Judge.h"

#include <SFML/Window/Event.hpp>

#include <sstream>

Judge::Judge(sf::RenderWindow* window) 
	: GameState(window),
	  texto("Você não vai ver isso :P", sf::FloatRect(0.f, 0.f, 640.f, 480.f), false, "Fontes/UI.ttf")
{
	sair = false;
}

void Judge::draw() {
	window->clear();

	texto.draw(*window);

	window->display();
}

void Judge::update() {
	const float deltaTime = getDeltaTime();

	texto.update();
}

void Judge::handleInput() {
	sf::Event e;

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window->close();
	}
}

void Judge::julgar(const Player& player) {
	
}

bool Judge::works() const {
	return GameState::works() && !sair;
}