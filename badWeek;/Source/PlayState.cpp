#include "PlayState.h"

#include <SFML/Window/Event.hpp>

#include "FrameWork/Manager.h"

#include <fstream>

PlayState::PlayState(sf::RenderWindow* window) :
	GameState(window),
	pc({ 215.0f, 136.0f }, { .5f, .5f }),
	relogio(1, 6, 30)
{
	texturaFundo = TextureManager::carregar("Imagens/quarto.jpg");
	fundo = sf::Sprite(*texturaFundo);
	fundo.scale(1.2f, 1.2f);

	musica.openFromFile("Sounds/fundo.wav");
	musica.setLoop(true);
	musica.setVolume(20.f);
	musica.play();
}

PlayState::~PlayState() {
	std::ofstream arquivo("player.data", std::ios::binary);

	arquivo << player;
}

void PlayState::draw() {
	window->clear();

	window->draw(fundo);
	pc.draw(*window);
	relogio.draw(*window);
	player.draw(*window);

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
	relogio.update(deltaTime);

	if (!pc.taLigado() || pc.getPaginaAtual() != PRINCIPAL) 
		relogio.setRapido(true);
	else
		relogio.setRapido(false);

	if (pc.taLigado()) {
		if (pc.getPaginaAtual() == NAVEGAR)
			player.modificarFelicidade(deltaTime * relogio.getModificador(), 1);
		else if (pc.getPaginaAtual() == CODAR)
			player.modificarFelicidade(deltaTime * relogio.getModificador(), -1);
		player.modificarSono(deltaTime * relogio.getModificador(), 1);
	}
	else 
		player.modificarSono(deltaTime * relogio.getModificador(), -1);
	
	if (pc.terminouProgramar())
		player.quantCodigos++;
	
	player.update();
	fundo.setColor(relogio.getColor());
}

bool PlayState::works() const {
	return GameState::works() && !(relogio.acabouTempo() || pc.getPaginaAtual() == MANDAR_PROJETO || player.morreu());
}