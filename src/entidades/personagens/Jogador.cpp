#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Jogador::Jogador(float posX, float posY, int n, int p) : Personagem(posX, posY, 40.0f, 40.0f, n), pontos(p)
        {
            setVel_Max(4);
            aplicarTextura(Gerenciadores::Jogador);
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
                float novoX = x + deslocamentoX;
                float novoY = y + deslocamentoY;

                setPosicao(novoX, novoY);
            }
        }

        void Jogador::atirar()
        {

        }

        void Jogador::setDirecao(int num)
        {
            if (num < 0) direcao = -1;
            else direcao = 1;
        }

        int Jogador::getDirecao() const
        {
            return direcao;
        }
        
    }
}