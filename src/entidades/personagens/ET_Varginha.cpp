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
              multiplicador_forca(ml), querAtirar(false), estressado(false)
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

            if (relogioTeleporte.getElapsedTime().asSeconds() >= 1.0f)
            {
                float range = 100.0f;
                float deslocamentoAleatorio = (((float)std::rand() / (float)RAND_MAX) * (2.0f * range)) - range;

                float novoX = posicaoInicial.x + deslocamentoAleatorio;

                setPosicao(sf::Vector2f(novoX, getPosicao().y));

                setVelocidade(sf::Vector2f(0.0f, getVelocidade().y));

                if (pJogador)
                {
                    float direcaoX = (pJogador->getPosicao().x < getPosicao().x) ? -1.0f : 1.0f;
                    pSprite->setScale(direcaoX * std::abs(pSprite->getScale().x), pSprite->getScale().y);
                }

                relogioTeleporte.restart();
            }
        }

        void ET_Varginha::danificar(Jogador *p)
        {
            if (p)
            {
                multiplicador_forca++;
                p->recebeDano(nivel_maldade * multiplicador_forca);
                p->ficarConfuso();
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

            for (int i = 0; i < (int)jogadores.size(); ++i)
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
            pProjetil->setpAlien(this);
            vetorProjeteis.push_back(pProjetil);
            vida_atual++;

            querAtirar = false;
            relogioTiro.restart();
        }

        std::vector<Projetil *> *ET_Varginha::getVetorProjeteis()
        {
            return &vetorProjeteis;
        }

        int ET_Varginha::get_num_vidas() const
        {
            return num_vidas + vetorProjeteis.size();
        }

        void ET_Varginha::executar()
        {
            mover();

            if (verificaPlayerArea() && relogioTiro.getElapsedTime().asSeconds() >= cooldownTiros)
            {
                querAtirar = true;
            }

            int max_vidas = get_num_vidas();
            if (vida_atual > max_vidas)
            {
                vida_atual = max_vidas;
            }

            bool estressadoAtual = !vetorProjeteis.empty();
            if (estressadoAtual != estressado)
            {
                estressado = estressadoAtual;

                float direcao = (pSprite->getScale().x < 0.0f) ? -1.0f : 1.0f;

                if (estressado)
                    aplicarTextura(Gerenciadores::ET_Varginha_Estressado);
                else
                    aplicarTextura(Gerenciadores::ET_Varginha);

                pSprite->setScale(direcao * std::abs(pSprite->getScale().x), pSprite->getScale().y);
            }
        }
    }
}