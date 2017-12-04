#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) : window(window) {
	timePoint = std::chrono::steady_clock::now();
}

GameState::~GameState() {
	window = nullptr;
}

bool GameState::works() const {
	return window->isOpen();
}

float GameState::getDeltaTime() {
	auto newTimePoint = std::chrono::steady_clock::now();
	float deltaTime = std::chrono::duration<float>(newTimePoint - timePoint).count();
	timePoint = newTimePoint;

	return deltaTime;
}
