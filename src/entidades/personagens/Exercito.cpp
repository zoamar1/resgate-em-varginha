#include "personagens/Exercito.hpp"
#include "personagens/Jogador.hpp"
#include <cmath>

namespace Entidades
{
    namespace Personagens
    {
        Exercito::Exercito(float posX, float posY, int n, int maldade, int r)
            : Inimigo(posX, posY, n, maldade), raio(r),
              pJogador(NULL), cooldownTiros(0.2f), querAtirar(false)
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

        void Exercito::setJogador(Jogador *pJ)
        {
            pJogador = pJ;
        }

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

        bool Exercito::verificaPlayerArea()
        {
            if (!pJogador)
                return false;

            sf::Vector2f posExercito = getPosicao();
            sf::Vector2f posJogador = pJogador->getPosicao();

            float x = posJogador.x - posExercito.x;
            float y = posJogador.y - posExercito.y;
            float distancia = std::sqrt(x * x + y * y);

            return distancia <= static_cast<float>(raio);
        }

        bool Exercito::getQuerAtirar()
        {
            return querAtirar;
        }

        void Exercito::atirar(Entidades::Projetil *pProjetil)
        {
            if (!pProjetil || !pJogador)
                return;

            sf::Vector2f posExercito = getPosicao();
            sf::Vector2f tamExercito = getpFig()->getSize();

            sf::Vector2f centroExercito = sf::Vector2f(posExercito.x + tamExercito.x / 2.0f, posExercito.y + tamExercito.y / 2.0f);

            sf::Vector2f posJogador = pJogador->getPosicao();
            sf::Vector2f tamJogador = pJogador->getpFig()->getSize();

            sf::Vector2f centroJogador = sf::Vector2f(posJogador.x + tamJogador.x / 2.0f, posJogador.y + tamJogador.y / 2.0f);

            float x = centroJogador.x - centroExercito.x;
            float y = centroJogador.y - centroExercito.y;
            float distancia = std::sqrt(x * x + y * y);

            if (distancia == 0.0f)
                return;

            float velocidadeProjetil = 10.0f;
            float velX = (x / distancia) * velocidadeProjetil;
            float velY = (y / distancia) * velocidadeProjetil;

            pProjetil->setPosicao(centroExercito);
            pProjetil->setVelocidade(sf::Vector2f(velX, velY));
            pProjetil->setDono(this);
            pProjetil->setAtivo(true);

            querAtirar = false;
            relogioTiro.restart();
        }

        void Exercito::salvar()
        {
        }

        void Exercito::executar()
        {
            mover();

            if (verificaPlayerArea() && relogioTiro.getElapsedTime().asSeconds() >= cooldownTiros)
            {
                querAtirar = true;
            }
        }
    }
}