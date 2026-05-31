#include "personagens/ET_Varginha.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        ET_Varginha::ET_Varginha(float posX, float posY, int n, int maldade, int ml) : Inimigo(posX, posY, n, maldade), multiplicador_laser(ml)
        {
        }

        ET_Varginha::~ET_Varginha() {}

        void ET_Varginha::danificar(Jogador *p)
        {
            if (p)
            {
                p->recebeDano(nivel_maldade);

                float distanciaTeletransporte = 150.0f;

                sf::Vector2f posJogador = p->getPosicao();
                sf::Vector2f minhaPos = this->getPosicao();

                float novaPosicaoX;

                if (minhaPos.x > posJogador.x)
                {
                    novaPosicaoX = posJogador.x - distanciaTeletransporte;
                }
                else
                {
                    novaPosicaoX = posJogador.x + distanciaTeletransporte;
                }

                this->setPosicao(sf::Vector2f(novaPosicaoX, posJogador.y));
            }
        }

        void ET_Varginha::executar()
        {
        }
    }
}