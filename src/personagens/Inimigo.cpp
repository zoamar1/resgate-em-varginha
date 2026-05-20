#include "personagens/Inimigo.hpp"

namespace Personagens
{
    Inimigo::Inimigo(int posX, int posY, int n, int maldade) : Personagem(posX, posY, n), nivel_maldade(n)
    {
    }

    Inimigo::~Inimigo() {}
}