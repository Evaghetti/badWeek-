#include "Player.h"
#include "Rand.h"

#include <iostream>
#include <sstream>

Player::Player() {
	Random random;

	felicidade = 100.f;
	sono = 0.f;

	porcSono = random.range(2.f, 4.f);
	porcFelicidade = random.range(4.f, 8.f);

	texto = Writer(toString(), { 10.f, 100.f, 100.f, 100.f }, true, "Fontes/relogio.ttf");
	texto.update();
	texto.setFontColor(sf::Color::White);
}

void Player::update() {
	texto.setMensagem(toString());
	texto.update();
}

void Player::modificarSono(const float deltaTime, const int mod) {
	if (sono >= 0.f && sono <= 100.f)
		sono += (deltaTime * porcSono) * mod;
}

void Player::modificarFelicidade(const float deltaTime, const int mod) {
	if (felicidade > 0.f && felicidade <= 100.f)
		felicidade += (deltaTime * porcFelicidade) * mod;
}

void Player::draw(sf::RenderTarget& target) {
	texto.draw(target);
}

std::string Player::toString() const {
	std::stringstream sb;
	
	sb << "FELICIDADE: " << (int)felicidade << "\n\n" << "SONO: " << (int)sono;
	return sb.str();
}

bool Player::morreu() const {
	return sono > 100.f || felicidade < 0.f;
}