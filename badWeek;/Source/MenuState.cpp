#include "MenuState.h"
#include "FrameWork/GUI/Button.h"
#include "FrameWork/Manager.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

MenuState::MenuState(sf::RenderWindow* window) : GameState(window) {
	texturaPC = TextureManager::carregar("Imagens/Computer.png");
	
	spritePC = sf::Sprite(*texturaPC);
	spritePC.setScale(.25f, .25f);
	spritePC.setPosition(425.f, 305.f);

	for (unsigned i = 0; i < botoes.size(); i++)
		botoes[i] = std::make_unique<Button>(sf::Vector2f(50.f , 150.f + (100.f * i)), sf::Vector2f(300.f, 75.f), "Teste");
}

void MenuState::draw() {
	window->clear({ 120, 120, 120, 255 });

	window->draw(spritePC);
	for (unsigned i = 0; i < botoes.size(); i++)
		botoes[i]->draw(*window);

	window->display();
}

void MenuState::handleInput() {
	sf::Event e;

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window->close();
		if (e.type == sf::Event::MouseMoved || e.type == sf::Event::MouseButtonPressed) {
			for (unsigned i = 0; i < botoes.size(); i++)
				botoes[i]->handleMouse(sf::Vector2f(sf::Mouse::getPosition(*window)));
		}
	}
}

void MenuState::update() {}

bool MenuState::works() const {
	return GameState::works() && !botoes.back()->foiUsado();
}