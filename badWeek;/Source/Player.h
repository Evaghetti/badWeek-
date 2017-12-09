#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include "FrameWork/Writer.h"
#include <fstream>

class Player {
	public:
		Player();
	
		void update();
		void draw(sf::RenderTarget& target);

		void modificarSono(const float deltaTime, const int mod);
		void modificarFelicidade(const float deltaTime, const int mod);

		bool morreu() const;

		int quantCodigos;
		float sono, porcSono;
		float felicidade, porcFelicidade;
	public:
		friend std::ostream& operator<< (std::ofstream& arquivo, Player& player) {
			arquivo.write(reinterpret_cast<char*>(&player.felicidade), sizeof(player.felicidade));
			arquivo.write(reinterpret_cast<char*>(&player.sono), sizeof(player.sono));
			arquivo.write(reinterpret_cast<char*>(&player.quantCodigos), sizeof(player.quantCodigos));

			return arquivo;
		}
		friend std::istream& operator>> (std::ifstream& arquivo, Player& player) {
			arquivo.read(reinterpret_cast<char*>(&player.felicidade), sizeof(player.felicidade));
			arquivo.read(reinterpret_cast<char*>(&player.sono), sizeof(player.sono));
			arquivo.read(reinterpret_cast<char*>(&player.quantCodigos), sizeof(player.quantCodigos));
			return arquivo;
		}
	private:
		std::string toString() const;
	private:
		Writer texto;
};

