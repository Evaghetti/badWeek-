#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include <memory>

#include "FrameWork/Writer.h"

class Tempo {
	public:
		Tempo(int dia = 0, int hora = 0, int minuto = 0);
		void update(const float deltaTime);
		void draw(sf::RenderTarget& target);

		void setRapido(bool rapido);
		bool acabouTempo() const;

		float getModificador() const;

		sf::Color getColor();
	private:
		void updateColor();

		bool deDia() const;
		bool deNoite() const;
		std::string horarioToString() const;
	private:
		int dia, hora, minuto;
		float tempoPassado;
		bool rapido;

		sf::Color corHora;
		Writer texto;

		static constexpr float holdMinuto = .05f;
		static constexpr float modTempoNormal = .01f, modTempoRapido = 1.f;
		static constexpr int modCor = 30;
};

