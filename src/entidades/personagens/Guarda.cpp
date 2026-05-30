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

                float direcaoX;

                if (p->getX() > this->getX())
                {
                    direcaoX = 1.0f;
                }
                else
                {
                    direcaoX = -1.0f;
                }

                p->setVelX(direcaoX * 8.0f);
                p->setVelY(-5.0f);
            }
        }

        void Guarda::executar()
        {
            desenhar();
        }
    }
}