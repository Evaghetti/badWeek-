#include "Source/Engine.h"

//Código de teste. Remover depois.
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Source/FrameWork/GUI/Widget.h"
#include "Source/FrameWork/GUI/Button.h"

int main() {
	//Engine("badWeek;", 640, 480);
	sf::RenderWindow window(sf::VideoMode(640, 480), "GUI");
	Widget* teste = new Button({ 150.f, 200.f }, { 300.f, 150.f }, "Agora digitou algo muito legal :D");
	while (window.isOpen()) {
		sf::Event e;

		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::MouseMoved || e.type == sf::Event::MouseButtonPressed)
				teste->handleMouse(sf::Vector2f(sf::Mouse::getPosition(window)));
			if (e.type == sf::Event::KeyPressed)
				teste->handleInput();
		}

		if (teste->foiUsado()) 
			std::cout << "Usou a caixa :D" << std::endl;

		teste->update();

		window.clear();
		teste->draw(window);
		window.display();
	}
	delete teste;
	return 0;
}