#include "Player.h"
#include "FrameWork/Random.h"

#include <sstream>

Player::Player() {
	Random random;

	felicidade = 100.f;
	sono = 0.f;
	quantCodigos = 0;

	porcSono = random.range(2.f, 4.f);
	porcFelicidade = random.range(4.f, 6.f);

	texto = Writer(toString(), { 10.f, 100.f, 250.f, 500.f }, true, "Fontes/relogio.ttf");
	texto.update();
	texto.setFontColor(sf::Color::White);
}

void Player::update() {
	texto.setMensagem(toString());
	texto.update();
}

void Player::modificarSono(const float deltaTime, const int mod) {
	if ((mod < 0 && sono > 0.f) || (mod > 0 && sono < 120.f))
		sono += (deltaTime * porcSono) * mod;
}

void Player::modificarFelicidade(const float deltaTime, const int mod) {
	if ((mod < 0 && felicidade > -20.f) || (mod > 0 && felicidade < 100.f))
		felicidade += (deltaTime * porcFelicidade) * mod;
}

void Player::draw(sf::RenderTarget& target) {
	texto.draw(target);
}

std::string Player::toString() const {
	std::stringstream sb;
	
	sb << "HAPPINESS: " << (int)felicidade << "\n\n" << "SLEEP: " << (int)sono
	   << "\n\n" << "PROGRAMS MADE: " << quantCodigos;
	return sb.str();
}

bool Player::morreu() const {
	return sono >= 120.f || felicidade <= -20.f;
}