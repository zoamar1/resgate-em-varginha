#include "personagens/Guarda.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {

        Guarda::Guarda(float posX, float posY, int n, int maldade, int f)
            : Inimigo(posX, posY, n, maldade),
              forca(f)
        {
            setVel_Max(1.0f);
            setVelocidade(sf::Vector2f(1.0f, 0.0f));

            if (pFig)
            {
                pFig->setSize(sf::Vector2f(70.0f, 197.0f));
                pFig->setPosition(sf::Vector2f(posX, posY));
            }

            aplicarTextura(Gerenciadores::Guarda);
        }

        Guarda::~Guarda() {}

        void Guarda::danificar(Jogador *p)
        {
            if (p)
            {
                p->recebeDano(nivel_maldade * forca);
            }
        }

        void Guarda::atirar(Entidades::Projetil *pProjetil)
        {
            // nao faz nada
        }

        void Guarda::mover()
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

        void Guarda::salvar()
        {
        }

        void Guarda::executar()
        {
            mover();
        }
    }
}