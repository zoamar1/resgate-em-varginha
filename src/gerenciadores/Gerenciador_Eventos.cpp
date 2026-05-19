#include "gerenciadores/Gerenciador_Eventos.hpp"

namespace Gerenciadores
{
    Gerenciador_Eventos *Gerenciador_Eventos::pEvento(NULL);
    Gerenciador_Eventos::Gerenciador_Eventos() : pGG(NULL) {

                                                 };

    Gerenciador_Eventos::~Gerenciador_Eventos()
    {
        pGG = NULL;
    }

    Gerenciador_Eventos *Gerenciador_Eventos::getGerenciador_Eventos()
    {
        if (!pEvento)
            pEvento = new Gerenciador_Eventos();
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
            if (evento.type == sf::Event::KeyPressed)
            {
                if(evento.key.code == sf::Keyboard::Escape)
                {
                    pGG->fecharJanela();
                }
            }
        }
    }

}
