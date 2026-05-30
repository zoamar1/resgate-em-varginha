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
                p->recebeDano(nivel_maldade);

                int direcaoX;

                if (p->getX() > this->getX())
                {
                    direcaoX = 1;
                }
                else
                {
                    direcaoX = -1;
                }

                p->setX(direcaoX * 8);
                p->setY(-5);
            }
        }

        void Guarda::executar()
        {
            desenhar();
        }
    }
}