#include "personagens/Inimigo.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Inimigo::Inimigo(float posX, float posY, int n, int maldade)
            : Personagem(posX, posY, 70.0f, 127.0f, n),
              nivel_maldade(maldade),
              posicaoInicial(posX, posY)
        {
        }

        Inimigo::~Inimigo() {}
    }
}