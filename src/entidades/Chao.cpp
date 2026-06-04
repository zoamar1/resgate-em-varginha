#include "entidades/Chao.hpp"

namespace Entidades
{
    Chao::Chao(sf::Vector2f pos, sf::Vector2f tam) : Entidade(pos, tam),
                                                     largura(tam.x)
    {
        aplicarTextura(Gerenciadores::Chao);

        if (pFig && pFig->getTexture())
        {
            sf::Vector2u tamTextura = pFig->getTexture()->getSize();

            pFig->setSize(sf::Vector2f(static_cast<float>(tamTextura.x), static_cast<float>(tamTextura.y)));
            pFig->setOrigin(0.0f, 0.0f);
            pFig->setPosition(getPosicao());

            largura = static_cast<float>(tamTextura.x);
        }
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

    float Chao::getLargura() const
    {
        return largura;
    }
}