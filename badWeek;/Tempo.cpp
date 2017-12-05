#include "Tempo.h"

#include "Manager.h"

#include <sstream>

Tempo::Tempo(int dia, int hora, int minuto) {
	this->dia = dia;
	this->hora = hora;
	this->minuto = minuto;
	this->tempoPassado = 0.f;
	this->rapido = false;

	texto = Writer(horarioToString(), sf::FloatRect(10.f, 10.f, 100.f, 100.f), true, "Fontes/relogio.ttf");
	texto.setFontColor(sf::Color::White);
}

std::string Tempo::horarioToString() const {
	std::stringstream sb;

	sb << "Dia " << dia << "\n\n";
	
	if (hora < 10)
		sb << '0';
	sb << hora << ":";

	if (minuto < 10)
		sb << '0';
	sb << minuto;
	return sb.str();
}

void Tempo::draw(sf::RenderTarget& target) {
	texto.draw(target);
}

void Tempo::update(const float deltaTime) {
	if (!rapido)
		tempoPassado += deltaTime * modTempoNormal;
	else
		tempoPassado += deltaTime * modTempoRapido;
	if (tempoPassado > holdMinuto) {
		minuto++;
		if (minuto >= 60) {
			hora++;
			minuto = 0;
		}
		if (hora >= 24) {
			hora = 0;
			dia++;
		}

		tempoPassado = 0.f;
	}

	texto.setMensagem(horarioToString());
	texto.update();
}

void Tempo::setRapido(bool rapido) {
	this->rapido = rapido;
}

bool Tempo::acabouTempo() const {
	return dia > 3;
}