#pragma once
#include "FrameWork/GameState.h"
#include "Player.h"

class JudgeState : public GameState {
	public:
		JudgeState(sf::RenderWindow* window);

		void julgar();
		
		void draw() override;
		void update() override;
		void handleInput() override;

		bool works() const override;
	private:
		Writer texto;
		Player player;
		bool sair, leu;

		static constexpr int quantConseguir = 10;
};

