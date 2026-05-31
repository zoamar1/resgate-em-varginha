#include "personagens/Guarda.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Guarda::Guarda(float posX, float posY, int n, int maldade, int f) : Inimigo(posX, posY, n, maldade), forca(f)
        {
        }

        Guarda::~Guarda() {}

        void Guarda::danificar(Jogador *p)
        {
            if (p)
            {
                p->recebeDano(nivel_maldade);
            }
        }

        void Guarda::executar()
        {
        }
    }
}