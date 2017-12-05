#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include "Writer.h"

struct Player {
	Player();
	
	void update();
	void draw(sf::RenderTarget& target);

	void modificarSono(const float deltaTime, const int mod);
	void modificarFelicidade(const float deltaTime, const int mod);

	bool morreu() const;

	float sono, porcSono;
	float felicidade, porcFelicidade;
	
private:
	std::string toString() const;
private:
	Writer texto;
};

