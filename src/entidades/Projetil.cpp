#include "entidades/Projetil.hpp"

namespace Entidades
{
    Projetil::Projetil(int posX, int posY, bool flag, int dano) : Entidade(posX, posY), ativo(flag), dano(dano)
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
