#include "entidades/Chao.hpp"

namespace Entidades
{
    Chao::Chao() : Entidade(0.0f, static_cast<float>(ALTURA - 90), static_cast<float>(LARGURA), 30.0f, false)
    {
        if (pFig)
        {
            pFig->setFillColor(sf::Color::White);
            pFig->setSize(sf::Vector2f(static_cast<float>(LARGURA), 30.0f));
            pFig->setOrigin(0.0f, 0.0f);
            pFig->setPosition(sf::Vector2f(x, y));
        }
    }
    Chao::~Chao()
    {
    }

    void Chao::executar()
    {
        desenhar();
    }
    void Chao::salvar()
    {
    }
}