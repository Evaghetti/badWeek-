#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <memory>

#include "Writer.h"

class Tempo {
	public:
		Tempo(int dia = 0, int hora = 0, int minuto = 0);
		void update(const float deltaTime);
		void draw(sf::RenderTarget& target);

		std::string horarioToString() const;
	private:
		int dia, hora, minuto;
		float modificadorTempo, tempoPassado;
		static constexpr float holdMinuto = .05f;

		Writer texto;
};

