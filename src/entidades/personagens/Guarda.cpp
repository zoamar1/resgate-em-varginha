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

                float direcaoX;
                sf::Vector2f posJogador = p->getPosicao();
                sf::Vector2f posGuarda = this->getPosicao();

                if (posJogador.x > posGuarda.x)
                {
                    direcaoX = 1;
                }
                else
                {
                    direcaoX = -1;
                }

                p->setPosicao(sf::Vector2f(direcaoX * 8.0f, -5.0f));
            }
        }

        void Guarda::executar()
        {
        }
    }
}