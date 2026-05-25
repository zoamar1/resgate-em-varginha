#include "gerenciadores/Gerenciador_Eventos.hpp"
#include "Jogo.hpp"

namespace Gerenciadores
{
    Gerenciador_Eventos *Gerenciador_Eventos::pEvento(NULL);
    Gerenciador_Eventos::Gerenciador_Eventos(Jogo *pJ) : pGG(NULL), pJogo(pJ), pJog1(NULL) {
                                                         };

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
        if (evento.key.code == sf::Keyboard::Escape)
        {
            pGG->fecharJanela();
        }
        if (evento.key.code == sf::Keyboard::Enter)
        {
            if (estado == Jogo::MENU)
            {
                pJogo->setEstado(Jogo::FASE1);
            }
        }
        if (pJog1)
        {
            float velMax = pJog1->getVel_Max();

            if (evento.type == sf::Event::KeyPressed)
            {
                if (evento.key.code == sf::Keyboard::W)
                    pJog1->setVelY(-velMax);
                if (evento.key.code == sf::Keyboard::S)
                    pJog1->setVelY(velMax);
                if (evento.key.code == sf::Keyboard::A)
                    pJog1->setVelX(-velMax);
                if (evento.key.code == sf::Keyboard::D)
                    pJog1->setVelX(velMax);
            }
            else if (evento.type == sf::Event::KeyReleased)
            {
                if (evento.key.code == sf::Keyboard::W)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        pJog1->setVelY(velMax);
                    else
                        pJog1->setVelY(0);
                }
                if (evento.key.code == sf::Keyboard::S)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                        pJog1->setVelY(-velMax);
                    else
                        pJog1->setVelY(0);
                }
                if (evento.key.code == sf::Keyboard::A)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        pJog1->setVelX(velMax);
                    else
                        pJog1->setVelX(0);
                }
                if (evento.key.code == sf::Keyboard::D)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        pJog1->setVelX(-velMax);
                    else
                        pJog1->setVelX(0);
                }
            }
        }
    }
}