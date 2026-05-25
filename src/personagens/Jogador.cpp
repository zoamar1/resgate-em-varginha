#include "personagens/Jogador.hpp"
#include "entidades/Plataforma.hpp"

namespace Personagens
{
    Jogador::Jogador(int posX, int posY, int n, int p) : Personagem(posX, posY, 40, 40, n), pontos(p), pPlataforma(NULL)
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

    void Jogador::definirPlataforma(const Entidades::Obstaculos::Plataforma* plataforma)
    {
        pPlataforma = plataforma;
    }

    void Jogador::mover()
    {
        int deslocamentoX = velx;
        int deslocamentoY = 0;
        (vely<0)? deslocamentoY = vely : deslocamentoY = 4;
        float novoX = (float)getX() + deslocamentoX;
        float novoY = (float)getY() + deslocamentoY;
       
        if (pPlataforma && pFig)
        {
            sf::FloatRect limitesPlataforma = pPlataforma->getLimites();
            sf::FloatRect limitesJogador = pFig->getGlobalBounds();
            float baseAtual = limitesJogador.top + limitesJogador.height;
            float baseNova = novoY + limitesJogador.height / 2.0f;
            float topoPlataforma = limitesPlataforma.top;
            float esquerdaJogador = novoX - limitesJogador.width / 2.0f;
            float direitaJogador = novoX + limitesJogador.width / 2.0f;
            float esquerdaPlataforma = limitesPlataforma.left;
            float direitaPlataforma = limitesPlataforma.left + limitesPlataforma.width;

            if (deslocamentoY > 0 && baseAtual <= topoPlataforma && baseNova >= topoPlataforma && direitaJogador > esquerdaPlataforma && esquerdaJogador < direitaPlataforma)
            {
                novoY = topoPlataforma - limitesJogador.height / 2.0f;
                vely = 0;
            }
        }

        if (deslocamentoX != 0 || deslocamentoY != 0)
        {
            setPosicao((int)novoX, (int)novoY);
        }
    }
}