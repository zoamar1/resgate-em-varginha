#include "entidades/Personagem.hpp"

namespace Personagens
{
    Personagem::Personagem(int posX, int posY, int n) : Entidade(posX, posY), num_vidas(n)
    {
    }

    Personagem::~Personagem()
    {
    }

}
