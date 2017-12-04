#include "SmoothWrite.h"
#include "Manager.h"

#include <iostream>
#include <sstream>

SmoothWrite::SmoothWrite(const std::string& mensagem, const sf::FloatRect& caixa) {
	fonte = FontManager::carregar("Fontes/computador.ttf");
	texto = sf::Text("", *fonte);
	texto.setFillColor(sf::Color::White);
	this->caixa = caixa;

	ler(mensagem);
}

void SmoothWrite::update() {
	if (!palavraAtual.empty()) {
		formatar();
		texto.setString(texto.getString() + palavraAtual.front());
		palavraAtual.erase(palavraAtual.begin());

		if (palavraAtual.empty() && !palavras.empty()) {
			palavraAtual = palavras.front();
			palavras.erase(palavras.begin());
			
			texto.setString(texto.getString() + " ");
		}
	}
}

void SmoothWrite::draw(sf::RenderTarget& target) {
	target.draw(texto);
}

void SmoothWrite::ler(const std::string& mensagem) {
	std::stringstream sb(mensagem);
	std::string buffer;

	if (!palavras.empty())
		return;
	while (sb >> buffer)
		palavras.push_back(buffer);

	palavraAtual = palavras.front();
	palavras.erase(palavras.begin());
}

bool SmoothWrite::checarDentro(const sf::FloatRect& outro) const {
	return !(outro.left + outro.width >= caixa.left + caixa.width);
}

void SmoothWrite::formatar() {
	sf::Text temp(texto);
	temp.setString(temp.getString() + " " + palavraAtual);
	
	if (!checarDentro(temp.getGlobalBounds()))
		texto.setString(texto.getString() + "\n");
}