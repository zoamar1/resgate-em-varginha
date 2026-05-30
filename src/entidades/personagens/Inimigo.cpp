#include "personagens/Inimigo.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Inimigo::Inimigo(float posX, float posY, int n, int maldade) : Personagem(posX, posY, n), nivel_maldade(maldade)
        {
        }

        Inimigo::~Inimigo() {}
    }
}