#include "JudgeState.h"

#include <SFML/Window/Event.hpp>

#include <fstream>
#include <sstream>

JudgeState::JudgeState(sf::RenderWindow* window) 
	: GameState(window),
	  texto("", sf::FloatRect(1.f, 1.f, 640.f, 480.f), false, "Fontes/UI.ttf")
{
	leu = false;
	sair = false;

	tempoPassado = 0.f;
}

void JudgeState::draw() {
	window->clear();

	texto.draw(*window);

	window->display();
}

void JudgeState::update() {
	const float deltaTime = getDeltaTime();

	if (!leu) {
		std::ifstream arquivo("player.data", std::ios::binary);

		arquivo >> player;
		julgar();
		leu = true;
	}
	else {
		tempoPassado += deltaTime;
		if (tempoPassado > holdTime) {
			texto.update();
			tempoPassado = 0.f;
		}
	}
}

void JudgeState::handleInput() {
	sf::Event e;

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window->close();
		if (e.type == sf::Event::KeyPressed)
			sair = texto.done();
	}
}

void JudgeState::julgar() {
	std::stringstream fraseFinal;

	if (!player.morreu()) {
		//Final bom
		if (player.quantCodigos >= quantConseguir) {
			fraseFinal << "You managed to complete the project, your bosss is so happy that you received a promotion\n";
			
			if (player.felicidade >= 50.f)
				fraseFinal << "If you were happy before imagine it now! So much happiness has affected on your social life and on your code. Congratulations\n";
			if (player.sono <= 50.f)
				fraseFinal << "Now that you are sure that you will not lose you job, you can finally rest, but take care to not make history repeat itself.\n";
			fraseFinal << "THE END.";
			texto.setFontColor(sf::Color::Green);
		}
		//Final médio e ruim
		else {
			fraseFinal << "You couldn't make the deadline, ";
			//Final médio.
			if (player.quantCodigos >= quantConseguir / 2) {
				fraseFinal << "but your boss noticed how much you tried to make it in time and let you stay in the job.\n";
				if (player.felicidade <= 40.f)
					fraseFinal << "Although the people that work alongside you are mad at you for not making in it in time, they tried to make you be better when noticed that you were not happy with the situation\n";
				else if (player.sono >= 80.f)
					fraseFinal << "Now that you may stay on your job, you decide to rest enough to recover the wasted time working, doesn't it sound familiar?\n";
				fraseFinal << "Even though your ending wasn't sad, don't you think it could have been better?";
				texto.setFontColor(sf::Color::White);
			}
			//Final ruim.
			else {
				fraseFinal << "and since you have done basically nothing in this week, your boss has fired you.\n";
				
				if (player.felicidade < 20.f)
					fraseFinal << "You are mentally and physically ill, and this news was the last drop of water that you nedeed. On the next night you committed suicide.\n";
				fraseFinal << "How good would it be if life had a way to restart right?";
				texto.setFontColor(sf::Color::Red);
			}
		}
	}
	else {
		if (player.felicidade <= -20.f)
			fraseFinal << "After so much time programming, you start to think if all of this evens is worth it , after much tought on the matter, you end up commiting suicide on a unkwon place, where no one can find your body.\n";
		else if (player.sono >= 120.f)
			fraseFinal << "The progress on the project is going weel, but you're starting to get tired of programming and remembers that you even havent had dinner and, since there was no food on your house, decides to go to a fast food, but on the way to there you fell insleep and crashes on a tree. you die the next die on the hospital.\n";
		fraseFinal << "YOU DIED.";
		texto.setFontColor(sf::Color::Red);
	}
	texto.setMensagem(fraseFinal.str());
}

bool JudgeState::works() const {
	return GameState::works() && !sair;
}

ChangeState JudgeState::qualTrocar() const {
	if (window->isOpen())
		return MENU;
	else
		return NENHUM;
}