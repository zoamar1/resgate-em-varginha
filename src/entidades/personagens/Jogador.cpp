#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Jogador::Jogador(float posX, float posY, int n, int p) : Personagem(posX, posY, 40.0f, 40.0f, n), pontos(p)
        {
            setVel_Max(4);
        }

        Jogador::~Jogador()
        {
        }

        void Jogador::executar()
        {
            mover();
            desenhar();
        }

        void Jogador::salvar()
        {
        }

        void Jogador::mover()
        {
            float deslocamentoX = velx;
            float deslocamentoY = vely;

            if (deslocamentoX != 0 || deslocamentoY != 0)
            {
                float novoX = getX() + deslocamentoX;
                float novoY = getY() + deslocamentoY;

                setPosicao(novoX, novoY);
            }
        }
    }
}