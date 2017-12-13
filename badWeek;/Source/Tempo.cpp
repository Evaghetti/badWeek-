#include "Tempo.h"

#include "FrameWork/Manager.h"

#include <sstream>

Tempo::Tempo(int dia, int hora, int minuto) {
	this->dia = dia;
	this->hora = hora;
	this->minuto = minuto;
	this->tempoPassado = 0.f;
	this->rapido = false;

	texto = Writer(horarioToString(), { 10.f, 10.f, 320.f, 240.f }, true, "Fontes/relogio.ttf");
	texto.update();
	texto.setFontColor(sf::Color::White);

	if (deDia())
		corHora = sf::Color(hora * modCor, hora * modCor, hora * modCor, 255);
	else if (deNoite())
		corHora = sf::Color(hora * modCor, hora * modCor, hora * modCor, 255);
}

std::string Tempo::horarioToString() const {
	std::stringstream sb;

	sb << "DAY " << dia << "\n\n";
	
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
			updateColor();
		}
		if (hora >= 24) {
			hora = 0;
			dia++;
			updateColor();
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

bool Tempo::deDia() const {
	return hora >= 5 && hora <= 12;
}

bool Tempo::deNoite() const {
	return hora >= 20 || hora <= 0;
}

float Tempo::getModificador() const {
	if (rapido)
		return modTempoRapido;

	return modTempoNormal;
}

void Tempo::updateColor() {
	if (deDia())
		corHora += sf::Color(modCor, modCor, modCor, 255);
	else if (deNoite())
		corHora -= sf::Color(modCor, modCor, modCor, 0);
}

sf::Color Tempo::getColor() { 
	return corHora;
}