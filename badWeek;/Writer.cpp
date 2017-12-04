#include "Writer.h"
#include "Manager.h"

#include <iostream>
#include <sstream>

Writer::Writer(const std::string& mensagem, const sf::FloatRect& caixa, bool instantaneo) {
	fonte = FontManager::carregar("Fontes/computador.ttf");
	texto = sf::Text("", *fonte);
	texto.setFillColor(sf::Color::White);
	this->caixa = caixa;
	this->instantaneo = instantaneo;
	ler(mensagem);

	//Gambiarras :D
	if (instantaneo)
		update();
}

void Writer::update() {
	if (!instantaneo) {
		if (!palavraAtual.empty())
			escrever();
	}
	else {
		while (!palavraAtual.empty())
			escrever();
	}
}

void Writer::escrever() {
	formatar();
	texto.setString(texto.getString() + palavraAtual.front());
	palavraAtual.erase(palavraAtual.begin());

	if (palavraAtual.empty() && !palavras.empty()) {
		palavraAtual = palavras.front();
		palavras.erase(palavras.begin());

		texto.setString(texto.getString() + " ");
	}
}

void Writer::draw(sf::RenderTarget& target) {
	target.draw(texto);
}

void Writer::ler(const std::string& mensagem) {
	std::stringstream sb(mensagem);
	std::string buffer;

	if (!palavras.empty())
		return;
	while (sb >> buffer)
		palavras.push_back(buffer);

	palavraAtual = palavras.front();
	palavras.erase(palavras.begin());
}

bool Writer::checarDentro(const sf::FloatRect& outro) const {
	return !(outro.left + outro.width >= caixa.left + caixa.width);
}

void Writer::formatar() {
	sf::Text temp(texto);
	temp.setString(temp.getString() + " " + palavraAtual);
	
	if (!checarDentro(temp.getGlobalBounds()))
		texto.setString(texto.getString() + "\n");
}