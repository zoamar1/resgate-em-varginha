#include "personagens/Inimigo.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Inimigo::Inimigo(float posX, float posY, int n, int maldade) : Personagem(posX, posY, 0.0f, 0.0f, n), nivel_maldade(maldade)
        {
        }

        Inimigo::~Inimigo() {}

        void Inimigo::salvar()
        {
        }
    }
}