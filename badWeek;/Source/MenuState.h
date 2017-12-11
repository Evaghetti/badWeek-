#pragma once
#include "FrameWork/GameState.h"
#include "FrameWork/GUI/Widget.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>
#include <array>

class MenuState : public GameState {
	public:
		MenuState(sf::RenderWindow* window);

		void draw() override;
		void handleInput() override;
		void update() override;

	private:
		sf::Sprite spritePC;

		std::shared_ptr<sf::Texture> texturaPC;
		std::array<std::unique_ptr<Widget>, 3> botoes;
};