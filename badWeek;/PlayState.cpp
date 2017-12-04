#include "PlayState.h"
#include <SFML/Window/Event.hpp>

PlayState::PlayState(sf::RenderWindow* window) :
	GameState(window),
	pc({ 0.0f, 0.0f }, {.5f, .5f}) 
{
}

void PlayState::draw() {
	window->clear();

	pc.draw(*window);

	window->display();
}

void PlayState::handleInput() {
	sf::Event e;

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window->close();
		else if (e.type == sf::Event::TextEntered)
			pc.handleInput(static_cast<char>(e.text.unicode));
	}
}

void PlayState::update() {
	const float deltaTime = getDeltaTime();
}
