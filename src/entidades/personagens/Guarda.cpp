#include "personagens/Guarda.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Guarda::Guarda(int posX, int posY, int n, int maldade, int f) : Inimigo(posX, posY, n, maldade), forca(f)
        {
        }

        Guarda::~Guarda() {}

        void Guarda::danificar(Jogador *p)
        {
            if (p)
            {
                p->recebeDano(forca);
            }
        }

        void Guarda::executar()
        {
            desenhar();
        }
    }
}