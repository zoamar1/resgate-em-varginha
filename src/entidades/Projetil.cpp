#include "entidades/Projetil.hpp"

namespace Entidades
{
    Projetil::Projetil(int posX, int posY, bool flag) : Entidade(posX, posY), ativo(flag)
    {
    }

    Projetil::~Projetil()
    {
    }
}
