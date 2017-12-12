#include "MenuState.h"
#include "FrameWork/GUI/Button.h"
#include "FrameWork/Manager.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

MenuState::MenuState(sf::RenderWindow* window) : GameState(window) {
	titulo = Writer("badWeek;", { 0.f, 0.f, 640.f, 480.f }, true, "Fontes/UI.ttf");
	titulo.setFontSize(100.f);
	titulo.update();
	
	comoJogar = Writer(
		"Você é um estágiario de programador que deve acabar um projeto de um mês em \
		um três dias.\n\
		Não deixe sua felicidade chegar a -20, ou você entrará em depressão\n\
		Você pode aumentar sua felicidade navegando na internet.\n\
		Também cuide de seu sono, não deixe chegar a 120 ou algo de ruim pode \
		acontecer, durma desligando o computador no botão vermelho para recuperar seu sono.\n\
		Caso ache que o projeto já está pronto, mande para o seu chefe! Boa sorte!",
		{ 0.f, 0.f, 640.f, 480.f },
		false,
		"Fontes/UI.ttf"
	);
	comoJogar.setFontSize(20.f);

	texturaPC = TextureManager::carregar("Imagens/Computer.png");
	
	spritePC = sf::Sprite(*texturaPC);
	spritePC.setScale(.25f, .25f);
	spritePC.setPosition(425.f, 305.f);

	botoes[0] = std::make_unique<Button>(sf::Vector2f(50.f , 150.f + (100.f * 0)), sf::Vector2f(300.f, 75.f), "Jogar");
	botoes[1] = std::make_unique<Button>(sf::Vector2f(50.f, 150.f + (100.f * 1)), sf::Vector2f(300.f, 75.f), "Como jogar");
	botoes[2] = std::make_unique<Button>(sf::Vector2f(50.f, 150.f + (100.f * 2)), sf::Vector2f(300.f, 75.f), "Sair");

	buttonAtual = 0;
}

void MenuState::draw() {
	window->clear({ 120, 120, 120, 255 });

	if (!instrucoes) {
		titulo.draw(*window);
		window->draw(spritePC);
		for (auto &it : botoes)
			it->draw(*window);
	}
	else {
		comoJogar.draw(*window);
	}

	window->display();
}

void MenuState::handleInput() {
	sf::Event e;

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window->close();
		if (e.type == sf::Event::MouseMoved || e.type == sf::Event::MouseButtonPressed) {
			for (auto &it : botoes)
				it->handleMouse(sf::Vector2f(sf::Mouse::getPosition(*window)));
		}
		if (e.type == sf::Event::KeyPressed) {
			if (!instrucoes) {
				switch (e.key.code) {
				case sf::Keyboard::Up:
					buttonAtual--;
					buttonAtual = buttonAtual % botoes.size();
					break;
				case sf::Keyboard::Down:
					buttonAtual++;
					if (unsigned(buttonAtual) >= botoes.size())
						buttonAtual = botoes.size() - 1;
					break;
				}

				botoes[buttonAtual]->handleInput();
			}
			else {
				comoJogar.setMensagem(
					"Você é um estágiario de programador que deve acabar um projeto de um mês em \
					um três dias.\n\
					Não deixe sua felicidade chegar a -20, ou você entrará em depressão\n\
					Você pode aumentar sua felicidade navegando na internet.\n\
					Também cuide de seu sono, não deixe chegar a 120 ou algo de ruim pode \
					acontecer, durma desligando o computador no botão vermelho para recuperar seu sono.\n\
					Caso ache que o projeto já está pronto, mande para o seu chefe! Boa sorte!"
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
	
	for (auto &it : botoes)
		it->update();
}

ChangeState MenuState::qualTrocar() const {
	if (!window->isOpen())
		return NENHUM;
	else
		return JOGAR;
}