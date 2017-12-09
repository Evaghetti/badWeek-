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
			fraseFinal << "Voc� conseguiu cumprir a meta dada pelo seu chefe! Ele est� t�o feliz que voc� recebeu uma promo��o\n";
			
			if (player.felicidade >= 50.f)
				fraseFinal << "Se antes voc� estava feliz imagine agora! Tamanha felicidade refletiu nas sua vida social e nos seus c�digos, parab�ns!\n";
			if (player.sono <= 50.f)
				fraseFinal << "Agora que est� com sua vaga garantida, pode finalmente descansar, mas cuidado para n�o repetir essa situa��o.\n";
			fraseFinal << "FIM.";
			texto.setFontColor(sf::Color::Green);
		}
		//Final m�dio e ruim
		else {
			fraseFinal << "Voc� n�o conseguiu a meta dada pelo seu chefe, ";
			//Final m�dio.
			if (player.quantCodigos >= quantConseguir / 2) {
				fraseFinal << "no entanto ele percebe todo o esfor�o que voc� fez para conseguir terminar sua parte a tempo e permite que voc� fique com a vaga.\n";
				if (player.felicidade <= 40.f)
					fraseFinal << "Apesar de estarem brabos contigo por n�o ter terminado o projeto a tempo, os seus colegas come�aram a te ajudar a melhorar quando viram que voc� n�o estava muito feliz com a situa��o.\n";
				else if (player.sono >= 80.f)
					fraseFinal << "Agora com sua vaga garantida, voc� decide desncansar o suficiente para recuperar o tempo gasto trabalhando, isso n�o te soa familiar?\n";
				fraseFinal << "Talvez seu final n�o tenha sido triste, mas n�o acha que podia ter sindo melhor?";
				texto.setFontColor(sf::Color::White);
			}
			//Final ruim.
			else {
				fraseFinal << "e como ele percebeu que voc� fez nada para contribuir no projeto, ele decide demiti-lo.\n";
				
				if (player.felicidade < 20.f)
					fraseFinal << "Voc� estava abalado emocional e psicologicamente, e essa noticia de seu chefe foi a gota d'�gua. Na noite seguinte voc� comete suicidio.\n";
				fraseFinal << "Ah se na vida tivesse uma forma de tentar de novo n�?";
				texto.setFontColor(sf::Color::Red);
			}
		}
	}
	else {
		if (player.felicidade <= -20.f)
			fraseFinal << "Ap�s tanto programr, voc� come�a a pensar se vale realmente a pena isso tudo, e por conta de todo o abalo psicol�gico que passou durante os ultimos dias, acaba por cometer suicidio em algum lugar desconhecido, onde ningu�m pode achar seu corpo\n";
		else if (player.sono >= 120.f)
			fraseFinal << "At� que o progresso do projeto est� indo bem, mas voc� est� cansado de tanto programar e lembra que nem mesmo jantou e como n�o havia comida em casa decide ir para um fast food, por�m no caminho acaba dormindo no volante e bate numa arvore. Voc� morre um dia depois no hospital.\n";
		fraseFinal << "VOC� MORREU.";
		texto.setFontColor(sf::Color::Red);
	}

	texto.setMensagem(fraseFinal.str());
}

bool JudgeState::works() const {
	return GameState::works() && !sair;
}