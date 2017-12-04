#include "GameState.h"
#include "SmoothWrite.h"
#include "Computador.h"

class PlayState : public GameState {
	public:
		PlayState(sf::RenderWindow* window);
		void draw() override;
		void handleInput() override;
		void update() override;
	private:
		Computador pc;
		SmoothWrite mensagem;
};

