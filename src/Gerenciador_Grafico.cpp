#include "Gerenciador_Grafico.hpp"

namespace Gerenciadores
{
    Gerenciador_Grafico* Gerenciador_Grafico::pGrafico = NULL;

    Gerenciador_Grafico::Gerenciador_Grafico() : 
        window(sf::VideoMode(LARGURA, ALTURA), "Jogo mais foda de todos os tempos")
    {
        window.setFramerateLimit(60);
    }

    Gerenciador_Grafico* Gerenciador_Grafico::getGerenciador_Grafico()
    {
        if(!pGrafico) 
        {
            pGrafico = new Gerenciador_Grafico();
        }
        return pGrafico;
    }

    bool Gerenciador_Grafico::janelaAberta()
    {
        return window.isOpen();
    }   

    sf::RenderWindow* Gerenciador_Grafico::getWindow()
    {
        return &window;
    }

    void Gerenciador_Grafico::fecharJanela()
    {
        window.close();
    }

    void Gerenciador_Grafico::desenhaRect(sf::RectangleShape rect)
    {
        if (window.isOpen())
        {
            window.draw(rect);
        }
    }

    void Gerenciador_Grafico::desenhaJanela()
    {
        if(window.isOpen())
        {
            window.display();
        }
    }

    void Gerenciador_Grafico::limpaJanela()
    {
        if (window.isOpen())
        {
            window.clear();
        }
    }
} 
