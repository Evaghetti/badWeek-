#pragma once
#include "GameState.h"
#include "Player.h"
class Judge : public GameState {
	public:
		Judge(sf::RenderWindow* window);
		
		void julgar(const Player& player);
		
		void draw() override;
		void update() override;
		void handleInput() override;

		bool works() const override;
	private:
		Writer texto;
		bool sair;

		static constexpr int quantConseguir = 30;
};

