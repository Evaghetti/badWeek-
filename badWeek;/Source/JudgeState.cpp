#include "JudgeState.h"

#include <SFML/Window/Event.hpp>

#include <fstream>
#include <sstream>

JudgeState::JudgeState(sf::RenderWindow* window) 
	: GameState(window),
	  texto("", sf::FloatRect(0.f, 0.f, 640.f, 480.f), false, "Fontes/UI.ttf")
{
	leu = false;
	sair = false;
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
	else
		texto.update();
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
			fraseFinal << "Você conseguiu cumprir a meta dada pelo seu chefe! Ele está tão feliz que você recebeu uma promoção\n";
			
			if (player.felicidade >= 50.f)
				fraseFinal << "Se antes você estava feliz imagine agora! Tamanha felicidade refletiu nas sua vida social e nos seus códigos, parabéns!\n";
			if (player.sono <= 50.f)
				fraseFinal << "Agora que está com sua vaga garantida, pode finalmente descansar, mas cuidado para não repetir essa situação.\n";
			fraseFinal << "FIM.";
			texto.setFontColor(sf::Color::Green);
		}
		//Final médio e ruim
		else {
			fraseFinal << "Você não conseguiu a meta dada pelo seu chefe, ";
			//Final médio.
			if (player.quantCodigos >= quantConseguir / 2) {
				fraseFinal << "no entanto ele percebe todo o esforço que você fez para conseguir terminar sua parte a tempo e permite que você fique com a vaga.\n";
				if (player.felicidade <= 40.f)
					fraseFinal << "Apesar de estarem brabos contigo por não ter terminado o projeto a tempo, os seus colegas começaram a te ajudar a melhorar quando viram que você não estava muito feliz com a situação.\n";
				else if (player.sono >= 80.f)
					fraseFinal << "Agora com sua vaga garantida, você decide desncansar o suficiente para recuperar o tempo gasto trabalhando, isso não te soa familiar?\n";
				fraseFinal << "Talvez seu final não tenha sido triste, mas não acha que podia ter sindo melhor?";
				texto.setFontColor(sf::Color::White);
			}
			//Final ruim.
			else {
				fraseFinal << "e como ele percebeu que você fez nada para contribuir no projeto, ele decide demiti-lo.\n";
				
				if (player.felicidade < 20.f)
					fraseFinal << "Você estava abalado emocional e psicologicamente, e essa noticia de seu chefe foi a gota d'água. Na noite seguinte você comete suicidio.\n";
				fraseFinal << "Ah se na vida tivesse uma forma de tentar de novo né?";
				texto.setFontColor(sf::Color::Red);
			}
		}
	}
	else {
		if (player.felicidade <= -20.f)
			fraseFinal << "Após tanto programr, você começa a pensar se vale realmente a pena isso tudo, e por conta de todo o abalo psicológico que passou durante os ultimos dias, acaba por cometer suicidio em algum lugar desconhecido, onde ninguém pode achar seu corpo\n";
		else if (player.sono >= 120.f)
			fraseFinal << "Até que o progresso do projeto está indo bem, mas você está cansado de tanto programar e lembra que nem mesmo jantou e como não havia comida em casa decide ir para um fast food, porém no caminho acaba dormindo no volante e bate numa arvore. Você morre um dia depois no hospital.\n";
		fraseFinal << "VOCÊ MORREU.";
		texto.setFontColor(sf::Color::Red);
	}

	texto.setMensagem(fraseFinal.str());
}

bool JudgeState::works() const {
	return GameState::works() && !sair;
}