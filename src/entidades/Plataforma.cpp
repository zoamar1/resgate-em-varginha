#include "entidades/Plataforma.hpp"

Entidades::Obstaculos::Plataforma::Plataforma(int posicaoX, int posicaoY, int largura, int altura)
{
    pFig->setSize({(float)largura, (float)altura});
    pFig->setOrigin({(float)largura / 2.0f, (float)altura / 2.0f});
    pFig->setPosition({(float)posicaoX, (float)posicaoY});
    pFig->setFillColor(sf::Color(120, 120, 120));
}

sf::FloatRect Entidades::Obstaculos::Plataforma::getLimites() const
{
    return pFig->getGlobalBounds();
}

void Entidades::Obstaculos::Plataforma::desenhar()
{
    Ente::desenhar();
}

void Entidades::Obstaculos::Plataforma::executar()
{
    // Plataformas estáticas não precisam executar lógica a cada frame
}

void Entidades::Obstaculos::Plataforma::salvar()
{
    // Persistência não implementada para plataformas neste exemplo
}