#include "PlayState.h"
#include <SFML/Window/Event.hpp>

PlayState::PlayState(sf::RenderWindow* window) :
	GameState(window),
	mensagem("Teste Maroto pra ver se a quebra de linhas pode funcionar nessa minha merda de vida :D", sf::FloatRect(0.0f, 0.0f, 640.0f, 480.0f)),
	pc({ 0.0f, 0.0f }, {.5f, .5f}) 
{
}

void PlayState::draw() {
	window->clear();

	mensagem.draw(*window);

	window->display();
}

void PlayState::handleInput() {
	sf::Event e;

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window->close();
		else if (e.type == sf::Event::TextEntered)
			mensagem.update();
	}
}

void PlayState::update() {
	const float deltaTime = getDeltaTime();
}
