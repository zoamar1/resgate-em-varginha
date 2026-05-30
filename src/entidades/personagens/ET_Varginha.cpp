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

                int distanciaTeletransporte = 150;

                int jogadorX = p->getX();
                int jogadorY = p->getY();

                int novaPosicaoX;

                if (this->getX() > jogadorX)
                {
                    novaPosicaoX = jogadorX - distanciaTeletransporte;
                }
                else
                {
                    novaPosicaoX = jogadorX + distanciaTeletransporte;
                }

                this->setX(novaPosicaoX);
                this->setY(jogadorY);
            }
        }

        void ET_Varginha::executar()
        {
            desenhar();
        }
    }
}