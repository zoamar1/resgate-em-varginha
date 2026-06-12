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
            cooldownTiros = 0.2f;
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

        void ET_Varginha::salvar()
        {
        }

        /*bool ET_Varginha::verificaPlayerArea()
        {
            if (!pJogador)
                return false;

            sf::Vector2f posExercito = getPosicao();
            sf::Vector2f posJogador = pJogador->getPosicao();

            float x = posJogador.x - posExercito.x;
            float y = posJogador.y - posExercito.y;
            float distancia = std::sqrt(x * x + y * y);

            return distancia <= static_cast<float>(raio);
        }*/

        bool ET_Varginha::getQuerAtirar()
        {
            return querAtirar;
        }

        void ET_Varginha::atirar(Entidades::Projetil *pProjetil)
        {
            /*if (!pProjetil || !pJogador)
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
            pProjetil->setDeJogador(false);
            pProjetil->setAtivo(true);

            querAtirar = false;
            relogioTiro.restart();*/
        }

        void ET_Varginha::executar()
        {
            mover();

            /* if (verificaPlayerArea() && relogioTiro.getElapsedTime().asSeconds() >= cooldownTiros)
             {
                 querAtirar = true;
             }*/
        }
    }
}