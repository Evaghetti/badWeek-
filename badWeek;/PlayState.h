#include "GameState.h"
#include "Writer.h"
#include "Computador.h"
#include "Tempo.h"

class PlayState : public GameState {
	public:
		PlayState(sf::RenderWindow* window);
		void draw() override;
		void handleInput() override;
		void update() override;
		bool works() const override;
	private:
		Computador pc;
		Tempo relogio;
};

