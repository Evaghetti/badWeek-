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
		if (e.type == sf::Event::TextEntered)
			pc.handleInput(static_cast<char>(e.text.unicode));
		if (e.type == sf::Event::MouseButtonPressed)
			pc.handleMouse(sf::Vector2f((float)e.mouseButton.x, (float)e.mouseButton.y));
	}
}

void PlayState::update() {
	const float deltaTime = getDeltaTime();
}
