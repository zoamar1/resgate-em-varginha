#include "personagens/ET_Varginha.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        ET_Varginha::ET_Varginha(int posX, int posY, int n, int maldade, int ml) : Inimigo(posX, posY, n, maldade), multiplicador_laser(ml)
        {
        }

        ET_Varginha::~ET_Varginha() {}

        void ET_Varginha::danificar(Jogador *p)
        {
            if (p)
            {
                p->recebeDano(nivel_maldade);

                float distanciaTeletransporte = 150.0f;

                float jogadorX = p->getX();
                float jogadorY = p->getY();

                float novaPosicaoX;

                if (this->getX() > jogadorX)
                {
                    novaPosicaoX = jogadorX - distanciaTeletransporte;
                }
                else
                {
                    novaPosicaoX = jogadorX + distanciaTeletransporte;
                }

                this->setX((int)novaPosicaoX);
                this->setY((int)jogadorY);
            }
        }

        void ET_Varginha::executar()
        {
            desenhar();
        }
    }
}