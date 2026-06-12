#include "personagens/ET_Varginha.hpp"
#include "personagens/Jogador.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include <cmath>

namespace Entidades
{
    namespace Personagens
    {
        Jogador *ET_Varginha::pJogador = NULL;

        ET_Varginha::ET_Varginha(float posX, float posY, int n, int maldade, int ml)
            : Inimigo(posX, posY, n, maldade),
              multiplicador_forca(ml), querAtirar(false)
        {
            cooldownTiros = 0.8f;
            setVel_Max(2.0f);
            setVelocidade(sf::Vector2f(2.0f, 0.0f));

            if (pFig)
            {
                pFig->setSize(sf::Vector2f(70.0f, 170.0f));
                pFig->setPosition(sf::Vector2f(posX, posY));
            }

            aplicarTextura(Gerenciadores::ET_Varginha);
            relogioTiro.restart();
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
                multiplicador_forca++;
                p->recebeDano(nivel_maldade * multiplicador_forca);
            }
        }

        void ET_Varginha::salvar()
        {
        }

        bool ET_Varginha::verificaPlayerArea()
        {
            Gerenciadores::Gerenciador_Colisoes *pGC = Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes();
            if (!pGC)
                return false;

            const std::vector<Jogador *> &jogadores = pGC->getJogadores();
            if (jogadores.empty())
                return false;

            sf::Vector2f posInimigo = getPosicao();
            Jogador *jogadorMaisProximo = NULL;
            float menorDistancia = -1.0f;
            float raioDesejado = 400.0f;

            for (size_t i = 0; i < jogadores.size(); ++i)
            {
                Jogador *pJog = jogadores[i];
                if (pJog)
                {
                    sf::Vector2f posJogador = pJog->getPosicao();
                    float x = posJogador.x - posInimigo.x;
                    float y = posJogador.y - posInimigo.y;
                    float distancia = std::sqrt(x * x + y * y);

                    if (menorDistancia < 0.0f || distancia < menorDistancia)
                    {
                        menorDistancia = distancia;
                        jogadorMaisProximo = pJog;
                    }
                }
            }

            if (jogadorMaisProximo && menorDistancia <= raioDesejado)
            {
                pJogador = jogadorMaisProximo;
                return true;
            }

            return false;
        }

        bool ET_Varginha::getQuerAtirar()
        {
            return querAtirar;
        }

        void ET_Varginha::atirar(Entidades::Projetil *pProjetil)
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
            pProjetil->setDeJogador(false);
            pProjetil->setAtivo(true);

            querAtirar = false;
            relogioTiro.restart();
        }

        void ET_Varginha::executar()
        {
            mover();

            if (verificaPlayerArea() && relogioTiro.getElapsedTime().asSeconds() >= cooldownTiros)
            {
                querAtirar = true;
            }
        }
    }
}