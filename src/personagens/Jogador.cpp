#include "personagens/Jogador.hpp"

namespace Personagens
{
    Jogador::Jogador(int posX, int posY, int n, int p) : Personagem(posX, posY, 40, 40, n), pontos(p)
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
        int deslocamentoX = velx;
        int deslocamentoY = vely;
       
        if (deslocamentoX != 0 || deslocamentoY != 0)
        {
            int novoX = getX() + deslocamentoX;
            int novoY = getY() + deslocamentoY;

            setPosicao(novoX, novoY);
        }
    }
}