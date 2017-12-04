#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) : window(window) {}

GameState::~GameState() {
	window = nullptr;
}

bool GameState::works() const {
	return window->isOpen();
}
