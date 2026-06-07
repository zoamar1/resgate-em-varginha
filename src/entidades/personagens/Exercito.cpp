#include "personagens/Exercito.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Exercito::Exercito(float posX, float posY, int n, int maldade, int r) : Inimigo(posX, posY, n, maldade), raio(r), posicaoInicial(posX, posY)
        {
            setVel_Max(1.4f);
            setVelocidade(sf::Vector2f(1.4f, 0.0f));

            if (pFig)
            {
                pFig->setSize(sf::Vector2f(70.0f, 127.0f));
                pFig->setPosition(sf::Vector2f(posX, posY));
            }

            aplicarTextura(Gerenciadores::Exercito);
        }

        Exercito::~Exercito() {}

        void Exercito::danificar(Jogador *p)
        {
            if (p)
            {
                p->recebeDano(nivel_maldade);
            }
        }

        void Exercito::mover()
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

        void Exercito::salva()
        {
        }

        void Exercito::executar()
        {
            mover();
        }

        void Exercito::atirar()
        {

        }
        int Exercito::verificaPlayerArea()
        {
            
        }
    }
}