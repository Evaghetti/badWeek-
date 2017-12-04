#include "GameState.h"
#include "Computador.h"

class PlayState : public GameState {
	public:
		PlayState(sf::RenderWindow* window);
		void draw() override;
		void handleInput() override;
		void update(const float deltaTime) override;
	private:
		Computador pc;
};

