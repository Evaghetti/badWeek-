#include <SFML\Graphics\RenderWindow.hpp>
#include <string>

class GameState {
	public:
		GameState(sf::RenderWindow* window);
		virtual ~GameState();
		virtual void handleInput() = 0;
		virtual void update(const float deltaTime) = 0;
		virtual void draw() = 0;

		bool works() const;
	protected:
		sf::RenderWindow* window;
};

