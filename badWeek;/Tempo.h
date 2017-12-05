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

		void setRapido(bool rapido);
		bool acabouTempo() const;
		bool deDia() const;

		float getModificador() const;
	private:
		std::string horarioToString() const;
	private:
		int dia, hora, minuto;
		float tempoPassado;
		bool rapido;

		static constexpr float holdMinuto = .05f;
		static constexpr float modTempoNormal = .01f, modTempoRapido = 1.f;

		Writer texto;
};

