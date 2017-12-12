#include "MenuState.h"
#include "FrameWork/GUI/Button.h"
#include "FrameWork/Manager.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

MenuState::MenuState(sf::RenderWindow* window) : GameState(window) {
	titulo = Writer("badWeek;", { 0.f, 0.f, 640.f, 480.f }, true, "Fontes/UI.ttf");
	titulo.setFontSize(100.f);
	titulo.update();
	
	texturaPC = TextureManager::carregar("Imagens/Computer.png");
	
	spritePC = sf::Sprite(*texturaPC);
	spritePC.setScale(.25f, .25f);
	spritePC.setPosition(425.f, 305.f);

	botoes[0] = std::make_unique<Button>(sf::Vector2f(50.f , 150.f + (100.f * 0)), sf::Vector2f(300.f, 75.f), "Jogar");
	botoes[1] = std::make_unique<Button>(sf::Vector2f(50.f, 150.f + (100.f * 1)), sf::Vector2f(300.f, 75.f), "Créditos");
	botoes[2] = std::make_unique<Button>(sf::Vector2f(50.f, 150.f + (100.f * 2)), sf::Vector2f(300.f, 75.f), "Sair");
}

void MenuState::draw() {
	window->clear({ 120, 120, 120, 255 });

	titulo.draw(*window);
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