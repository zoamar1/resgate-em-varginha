#include "gerenciadores/Gerenciador_Eventos.hpp"
#include "Jogo.hpp"

namespace Gerenciadores
{
    Gerenciador_Eventos *Gerenciador_Eventos::pEvento(NULL);
    Gerenciador_Eventos::Gerenciador_Eventos(Jogo *pJ) : pGG(NULL), pJogo(pJ), pJog1(NULL) { }

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

    void Gerenciador_Eventos::setJogador1(Personagens::Jogador* pJogador1)
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

        if (pJog1)
        {
            bool cima = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            bool baixo = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            bool esquerda = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            bool direita = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

            int x = (direita ? 1 : 0) + (esquerda ? -1 : 0);
            int y = (baixo ? 1 : 0) + (cima ? -1 : 0);

            float velMax = pJog1->getVel_Max();
            pJog1->setVelX(x * velMax);
            pJog1->setVelY(y * velMax);
        }
    }
}
