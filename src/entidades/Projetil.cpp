#include "entidades/Projetil.hpp"

Projetil::Projetil(int posX, int posY, bool flag) : Entidade(posX, posY), ativo(flag)
{
}

Projetil::~Projetil()
{
}