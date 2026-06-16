#include "gerenciadores/Gerenciador_Eventos.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "Jogo.hpp"

namespace Gerenciadores
{
    Gerenciador_Eventos *Gerenciador_Eventos::pEvento(NULL);

    Gerenciador_Eventos::Gerenciador_Eventos(Jogo *pJ)
        : pGG(NULL), pJogo(pJ), pJog1(NULL), pJog2(NULL) {}

    Gerenciador_Eventos::~Gerenciador_Eventos()
    {
        pGG = NULL;
        pJogo = NULL;
    }

    Gerenciador_Eventos *Gerenciador_Eventos::getGerenciador_Eventos(Jogo *pJ)
    {
        if (!pEvento)
            pEvento = new Gerenciador_Eventos(pJ);
        return pEvento;
    }

    void Gerenciador_Eventos::setGerenciador_Grafico(Gerenciador_Grafico *pGG)
    {
        this->pGG = pGG;
    }

    void Gerenciador_Eventos::setJogador1(Entidades::Personagens::Jogador *pJogador1)
    {
        pJog1 = pJogador1;
    }

    void Gerenciador_Eventos::setJogador2(Entidades::Personagens::Jogador *pJogador2)
    {
        pJog2 = pJogador2;
    }

    void Gerenciador_Eventos::executar()
    {
        if (!pGG || !pJogo)
            return;

        if (pJog1)
            controlaMovimentoJogador1();

        if (pJog2)
            controlaMovimentoJogador2();
    }

    void Gerenciador_Eventos::verificaTeclaPressionada(sf::Event &evento)
    {
        if (!pJogo || !pGG)
            return;

        Jogo::Estados estado = pJogo->getEstado();

        if (evento.type == sf::Event::KeyPressed &&
            evento.key.code == sf::Keyboard::Escape)
        {
            if (estado != Jogo::RANKING_TELA)
            {
                pGG->fecharJanela();
                return;
            }
        }

        if (evento.type == sf::Event::KeyPressed)
        {
            if (evento.key.code == sf::Keyboard::Num1 && estado == Jogo::MENU)
            {
                pJogo->setEstado(Jogo::CADASTRO_J1);
            }
            else if (evento.key.code == sf::Keyboard::Num2 && estado == Jogo::MENU)
            {
                pJogo->setEstado(Jogo::CADASTRO_J1_2P);
            }
            else if (evento.key.code == sf::Keyboard::Num3 && estado == Jogo::MENU)
            {
                pJogo->setEstado(Jogo::RANKING_TELA);
            }
        }

        if (evento.type == sf::Event::KeyPressed &&
            evento.key.code == sf::Keyboard::G)
        {
            if ((estado == Jogo::FASE1 || estado == Jogo::FASE2) && pJog1)
            {
                Fases::Fase *pFase = static_cast<Fases::Fase *>(pJogo->getCenarioAtual());
                if (pFase)
                {
                    Entidades::Projetil *pProjetil = pFase->getProjetilDisponivel();
                    if (pProjetil)
                    {
                        pJog1->atirar(pProjetil);
                        Gerenciador_Colisoes::getGerenciador_Colisoes()
                            ->registrarProjetilJogador(pProjetil, pJog1);
                    }
                }
            }
        }

        if (evento.type == sf::Event::KeyPressed &&
            evento.key.code == sf::Keyboard::P)
        {
            if ((estado == Jogo::FASE1 || estado == Jogo::FASE2) && pJog2)
            {
                Fases::Fase *pFase = static_cast<Fases::Fase *>(pJogo->getCenarioAtual());
                if (pFase)
                {
                    Entidades::Projetil *pProjetil = pFase->getProjetilDisponivel();
                    if (pProjetil)
                    {
                        pJog2->atirar(pProjetil);
                        Gerenciador_Colisoes::getGerenciador_Colisoes()
                            ->registrarProjetilJogador(pProjetil, pJog2);
                    }
                }
            }
        }
    }

    void Gerenciador_Eventos::controlaMovimentoJogador1()
    {
        if (!pJog1)
            return;

        bool esquerda = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool direita = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        if (pJog1->getConfuso())
        {
            bool temp = esquerda;
            esquerda = direita;
            direita = temp;
        }

        int x = (direita ? 1 : 0) + (esquerda ? -1 : 0);
        if (x != 0)
            pJog1->setDirecao(x);

        float velMax = pJog1->getVel_Max();
        float velY = pJog1->getVelocidade().y;
        pJog1->setVelocidade(sf::Vector2f(x * velMax, velY));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            pJog1->pular();
    }

    void Gerenciador_Eventos::controlaMovimentoJogador2()
    {
        if (!pJog2)
            return;

        bool esquerda = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool direita = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

        if (pJog2->getConfuso())
        {
            bool temp = esquerda;
            esquerda = direita;
            direita = temp;
        }

        int x = (direita ? 1 : 0) + (esquerda ? -1 : 0);
        if (x != 0)
            pJog2->setDirecao(x);

        float velMax = pJog2->getVel_Max();
        float velY = pJog2->getVelocidade().y;
        pJog2->setVelocidade(sf::Vector2f(x * velMax, velY));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            pJog2->pular();
    }
}