#include "Writer.h"
#include "Manager.h"

#include <iostream>
#include <sstream>

Writer::Writer(const std::string& mensagem, const sf::FloatRect& caixa, bool instantaneo) {
	fonte = FontManager::carregar("Fontes/computador.ttf");
	texto = sf::Text("", *fonte);
	texto.setFillColor(sf::Color::White);
	setRect(caixa);
	this->instantaneo = instantaneo;

	ler(mensagem);
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

		if (texto.getString()[texto.getString().getSize() - 1] != '\n')
			texto.setString(texto.getString() + " ");
	}
}

void Writer::draw(sf::RenderTarget& target) {
	target.draw(texto);
}

void Writer::ler(const std::string& mensagem) {
	std::stringstream linhas(mensagem), linhaAtual;
	std::string bufferLinha, bufferPalavra;
	int tabular = 0;

	while (std::getline(linhas, bufferLinha, '\n')) {
		linhaAtual = std::stringstream(bufferLinha);
		if (bufferLinha.find('}') != std::string::npos)
			tabular -= 4;

		if (tabular > 0)
			palavras.push_back(std::string(tabular, ' '));
		while (linhaAtual >> bufferPalavra)
			palavras.push_back(bufferPalavra);
		palavras.back() += '\n';
		
		if (bufferLinha.find('{') != std::string::npos)
			tabular += 4;
		
		std::cout << tabular << std::endl;
	}

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

void Writer::setRect(const sf::FloatRect& caixa) {
	this->caixa = caixa;
	texto.setPosition(caixa.left, caixa.top);
}

void Writer::setFontSize(const float tamanho) {
	texto.setCharacterSize((unsigned)tamanho);
}

void Writer::setFontColor(sf::Color cor) {
	texto.setFillColor(cor);
}

void Writer::setParams(const Writer & outro) {
	texto.setFillColor(outro.texto.getFillColor());
	setFontSize((float)outro.texto.getCharacterSize());
	setRect(outro.caixa);
}

void Writer::setMensagem(const std::string& mensagem) {
	if (!palavras.empty())
		return;

	ler(mensagem);
}