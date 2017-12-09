#include "FrameWork/GameState.h"
#include "FrameWork/Writer.h"
#include "Computador.h"
#include "Player.h"
#include "Tempo.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Music.hpp>

#include <memory>

class PlayState : public GameState {
public:
	PlayState(sf::RenderWindow* window);
	virtual ~PlayState();

	void draw() override;
	void handleInput() override;
	void update() override;
	bool works() const override;
private:
	Computador pc;
	Tempo relogio;
	Player player;

	std::shared_ptr<sf::Texture> texturaFundo;
	sf::Sprite fundo;
	sf::Music musica;
};

