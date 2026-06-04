#include "entidades/Projetil.hpp"

namespace Entidades
{
    Projetil::Projetil(float posX, float posY, bool flag, int dano) : Entidade(sf::Vector2f(posX, posY), sf::Vector2f(0.0f, 0.0f)), ativo(flag), dano(dano), pDono(this)
    {
        if (pFig)
        {
            pFig->setSize(sf::Vector2f(16.0f, 6.0f));
            pFig->setFillColor(sf::Color::Yellow);
            pFig->setPosition(getPosicao());
            setVelocidade({50.0f, 0.0f});
            setVel_Max(10.0f);
        }

    }

    Projetil::~Projetil()
    {
    }

    bool Projetil::getAtivo() const
    {
        return ativo;
    }

    bool Projetil::getDano() const
    {
        return dano;
    }

    void Projetil::mover()
    {
        sf::Vector2f deslocamento = getVelocidade();

        if (deslocamento.x != 0.0f || deslocamento.y != 0.0f)
        {
            setPosicao(getPosicao() + deslocamento);
        }
    }

    void Projetil::executar()
    {
        aplicarGravidade();
        mover();
    }
    void Projetil::salvar()
    {

    }

    Entidades::Entidade *Projetil::getDono()
    {
        return pDono;
    }
}
