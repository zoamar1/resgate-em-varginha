#include "entidades/Projetil.hpp"

namespace Entidades
{
    Projetil::Projetil(float posX, float posY, bool flag, int dano) : Entidade(sf::Vector2f(posX, posY), sf::Vector2f(0.0f, 0.0f), false), ativo(flag), dano(dano)
    {
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
}
