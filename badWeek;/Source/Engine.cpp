#include "Engine.h"
#include "FrameWork/Manager.h"

#include "PlayState.h"
#include "MenuState.h"
#include "JudgeState.h"
#include <SFML/Graphics/Image.hpp>

Engine::Engine(const std::string& nome, int largura, int altura)
	: window(sf::VideoMode(largura, altura), nome, sf::Style::Close | sf::Style::Titlebar)
	  
{
	sf::Image icon;
	icon.loadFromFile("icon.bmp");

	gameStates.push_back(std::make_unique<MenuState>(&window));
	//gameStates.push_back(std::make_unique<PlayState>(&window));
	//gameStates.push_back(std::make_unique<JudgeState>(&window));

	window.setIcon(850, 689, icon.getPixelsPtr());
	run();
}

void Engine::run() {
	while (!gameStates.empty()) {
		while (gameStates.front()->works()) {
			gameStates.front()->handleInput();
			gameStates.front()->update();
			gameStates.front()->draw();
		}

		gameStates.erase(gameStates.begin());
		
		TextureManager::liberar();
		FontManager::liberar();
		SoundBufferManager::liberar();
	}
}
