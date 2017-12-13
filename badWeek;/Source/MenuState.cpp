#include "MenuState.h"
#include "FrameWork/GUI/Button.h"
#include "FrameWork/Manager.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

MenuState::MenuState(sf::RenderWindow* window) : GameState(window) {
	titulo = Writer("badWeek;", { 0.f, 0.f, 640.f, 480.f }, true, "Fontes/UI.ttf");
	titulo.setFontSize(100.f);
	titulo.setOutline(5.f);
	titulo.update();
	
	comoJogar = Writer(
		"You are a programmr that has to finish a month old project\
		in a week.\n\
		Don't let your happiner drop down to -20, or you will start to be depressed\n\
		You can raise it by using the internet.\n\
		Also watch out for how much you sleep you need, if it gets to 120 something bad \
		may happen, you can sleep by pressing the red button on the monitor.\n\
		If you think the project is ready, send it to your boss! Good luck!",
		{ 0.f, 0.f, 640.f, 480.f },
		false,
		"Fontes/UI.ttf"
	);
	comoJogar.setFontSize(20.f);

	texturaPC = TextureManager::carregar("Imagens/Computer.png");
	texturaBackground = TextureManager::carregar("Imagens/menu background.jpg");

	spritePC = sf::Sprite(*texturaPC);
	spritePC.setScale(.25f, .25f);
	spritePC.setPosition(425.f, 305.f);

	spriteBackground = sf::Sprite(*texturaBackground);
	spriteBackground.setScale(1.5f, 1.75f);

	botoes[0] = std::make_unique<Button>(sf::Vector2f(50.f , 150.f + (100.f * 0)), sf::Vector2f(300.f, 75.f), "New Game");
	botoes[1] = std::make_unique<Button>(sf::Vector2f(50.f, 150.f + (100.f * 1)), sf::Vector2f(300.f, 75.f), "How to play");
	botoes[2] = std::make_unique<Button>(sf::Vector2f(50.f, 150.f + (100.f * 2)), sf::Vector2f(300.f, 75.f), "Exit");

	musica.openFromFile("Sounds/menu music.wav");
	musica.setLoop(true);
	musica.setVolume(20.f);
	musica.play();

	buttonAtual = 0;
}

void MenuState::draw() {
	window->clear({ 120, 120, 120, 255 });
	
	if (!instrucoes) {
		spriteBackground.setColor(sf::Color::White);
		window->draw(spriteBackground);

		titulo.draw(*window);
		window->draw(spritePC);
		
		for (auto &it : botoes)
			it->draw(*window);
	}
	else {
		spriteBackground.setColor({ 100, 100, 100, 255 });
		window->draw(spriteBackground);
		
		comoJogar.draw(*window);
	}

	window->display();
}

void MenuState::handleInput() {
	sf::Event e;

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window->close();
		if (e.type == sf::Event::MouseMoved || e.type == sf::Event::MouseButtonPressed && !instrucoes) {
			for (auto &it : botoes)
				it->handleMouse(sf::Vector2f(sf::Mouse::getPosition(*window)));
		}
		if (e.type == sf::Event::KeyPressed) {
			if (instrucoes && comoJogar.done()) {
				comoJogar.setMensagem(
					"You are a programmr that has to finish a month old project\
					in a week.\n\
					Don't let your happiner drop down to -20, or you will start to be depressed\n\
					You can raise it by using the internet.\n\
					Also watch out for how much you sleep you need, if it gets to 120 something bad \
					may happen, you can sleep by pressing the red button on the monitor.\n\
					If you think the project is ready, send it to your boss! Good luck!"
				);
				instrucoes = false;
			}
		}
	}
}

void MenuState::update() {
	if (!instrucoes)
		instrucoes = botoes[botoes.size() / 2]->foiUsado();
	else
		comoJogar.update();

	if (botoes.back()->foiUsado())
		window->close();
	
	for (unsigned i = 1; i < botoes.size(); i++)
		botoes[i]->update();
}

bool MenuState::works() const {
	return GameState::works() && !botoes.front()->foiUsado();
}

ChangeState MenuState::qualTrocar() const {
	if (window->isOpen())
		return JOGAR;
	else
		return NENHUM;
}