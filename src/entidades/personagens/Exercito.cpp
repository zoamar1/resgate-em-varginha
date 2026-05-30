#include "personagens/Exercito.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Exercito::Exercito(int posX, int posY, int n, int maldade, int p) : Inimigo(posX, posY, n, maldade), precisao(p)
        {
        }

        Exercito::~Exercito() {}

        void Exercito::danificar(Jogador *p)
        {
            if (p)
            {
                // falta concluir essa parte
            }
        }

        void Exercito::executar()
        {
            desenhar();
        }
    }
}