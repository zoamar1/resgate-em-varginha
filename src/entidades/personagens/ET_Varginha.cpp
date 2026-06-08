#include "personagens/ET_Varginha.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        ET_Varginha::ET_Varginha(float posX, float posY, int n, int maldade, int ml)
            : Inimigo(posX, posY, n, maldade),
              multiplicador_laser(ml)
        {
            setVel_Max(2.0f);
            setVelocidade(sf::Vector2f(2.0f, 0.0f));

            if (pFig)
            {
                pFig->setSize(sf::Vector2f(70.0f, 170.0f));
                pFig->setPosition(sf::Vector2f(posX, posY));
            }

            aplicarTextura(Gerenciadores::ET_Varginha);
        }

        ET_Varginha::~ET_Varginha() {}

        void ET_Varginha::mover()
        {
            aplicarGravidade();

            sf::Vector2f posicaoAtual = getPosicao();
            sf::Vector2f velAtual = getVelocidade();

            if (posicaoAtual.x > (posicaoInicial.x + 100) && velAtual.x > 0.0f)
            {
                setVelocidade(sf::Vector2f(-getVel_Max(), velAtual.y));
            }
            else if (posicaoAtual.x < (posicaoInicial.x - 100) && velAtual.x < 0.0f)
            {
                setVelocidade(sf::Vector2f(getVel_Max(), velAtual.y));
            }

            setPosicao(getPosicao() + getVelocidade());
        }

        void ET_Varginha::danificar(Jogador *p)
        {
            if (p)
            {
                // falta concluir essa parte
            }
        }

        void ET_Varginha::atirar(Entidades::Projetil *pProjetil)
        {
        }

        void ET_Varginha::salvar()
        {
        }

        void ET_Varginha::executar()
        {
            mover();
        }
    }
}