#include "gerenciadores/Gerenciador_Eventos.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "Jogo.hpp"

namespace Gerenciadores
{
    Gerenciador_Eventos *Gerenciador_Eventos::pEvento(NULL);
    Gerenciador_Eventos::Gerenciador_Eventos(Jogo *pJ) : pGG(NULL), pJogo(pJ), pJog1(NULL) {}

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

    void Gerenciador_Eventos::executar()
    {
        sf::Event evento;
        while (pGG->getWindow()->pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                pGG->fecharJanela();
            if (evento.type == sf::Event::KeyPressed || evento.type == sf::Event::KeyReleased)
                verificaTeclaPressionada(evento);
        }

        if (pJog1)
        {
            bool esquerda = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            bool direita = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

            int x = (direita ? 1 : 0) + (esquerda ? -1 : 0);
            float velMax = pJog1->getVel_Max();

            if (x >= 0) pJog1->setDirecao(1);
            else pJog1->setDirecao(-1);
            
            
            float velY = pJog1->getVelY();
            pJog1->setDirecao(x);
            pJog1->setVelocidade(sf::Vector2f(x * velMax, velY));
        }
    }

    void Gerenciador_Eventos::verificaTeclaPressionada(sf::Event &evento)
    {
        Jogo::Estados estado = pJogo->getEstado();
        if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
        {
            pGG->fecharJanela();
            return;
        }
        if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter)
        {
            if (estado == Jogo::MENU)
            {
                pJogo->setEstado(Jogo::FASE1);
            }
        }
        if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::G)
        {
            if ((estado == Jogo::FASE1 || estado == Jogo::FASE2) && pJog1)
            {
                Entidades::Projetil* novoProjetil = pJog1->atirar();
                Fases::Fase* pFase = static_cast<Fases::Fase*>(pJogo->getCenarioAtual());
                pFase->incluirProjetil(novoProjetil);
            }
        }
    }
}