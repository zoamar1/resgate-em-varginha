#include "entidades/Chao.hpp"

namespace Entidades
{
    Chao::Chao() : Entidade(sf::Vector2f(0.0f, static_cast<float>(ALTURA - 90)), sf::Vector2f(static_cast<float>(LARGURA), 30.0f), false)
    {
        if (pFig)
        {
            pFig->setSize(sf::Vector2f(static_cast<float>(LARGURA), 70.0f));
            pFig->setOrigin(0.0f, 0.0f);
            pFig->setPosition(getPosicao());
        }
        aplicarTextura(Gerenciadores::Chao);
    }
    Chao::~Chao()
    {
    }

    void Chao::executar()
    {
    }
    void Chao::salvar()
    {
    }
}