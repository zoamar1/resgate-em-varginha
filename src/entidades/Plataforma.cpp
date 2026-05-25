#include "entidades/Plataforma.hpp"

Plataforma::Plataforma(int posicaoX, int posicaoY, int largura, int altura)
{
    retangulo.setSize({(float)largura, (float)altura});
    retangulo.setOrigin({(float)largura / 2.0f, (float)altura / 2.0f});
    retangulo.setPosition({(float)posicaoX, (float)posicaoY});
    retangulo.setFillColor(sf::Color(120, 120, 120));
}

void Plataforma::desenhar()
{
    Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()->desenhaRect(retangulo);
}