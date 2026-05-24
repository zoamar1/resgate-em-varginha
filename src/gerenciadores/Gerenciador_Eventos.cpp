#include "gerenciadores/Gerenciador_Eventos.hpp"
#include "Jogo.hpp"

namespace Gerenciadores
{
    Gerenciador_Eventos *Gerenciador_Eventos::pEvento(NULL);
    Gerenciador_Eventos::Gerenciador_Eventos(Jogo* pJ) : pGG(NULL), pJogo(pJ) 
    {                                          
    };

    Gerenciador_Eventos::~Gerenciador_Eventos()
    {
        pGG = NULL;
        pJogo = NULL;
    }

    Gerenciador_Eventos *Gerenciador_Eventos::getGerenciador_Eventos(Jogo* pJ)
    {
        if (!pEvento)
            pEvento = new Gerenciador_Eventos(pJ);
        return pEvento;
    }

    void Gerenciador_Eventos::setGerenciador_Grafico(Gerenciador_Grafico *pGG)
    {
        this->pGG = pGG;
    }

    void Gerenciador_Eventos::executar()
    {
        sf::Event evento;
        while (pGG->getWindow()->pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                pGG->fecharJanela();
            verificaTeclaPressionada(evento);
        }
    }
    
    void Gerenciador_Eventos::verificaTeclaPressionada(sf::Event &evento)
    {
        if (evento.type == sf::Event::KeyPressed)
            {
                Jogo::Estados estado = pJogo->getEstado();
                if(evento.key.code == sf::Keyboard::Escape)
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
            }
    }
}