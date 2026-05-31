#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "entidades/Ente.hpp"

namespace Gerenciadores
{
    Gerenciador_Grafico *Gerenciador_Grafico::pGrafico = NULL;

    Gerenciador_Grafico::Gerenciador_Grafico() : window(sf::VideoMode(LARGURA, ALTURA), "Resgate em Varginha")
    {
        texturas.resize(7);
        window.setFramerateLimit(60);
        if (!texturas[Jogador].loadFromFile("assets/jogador.png"))
        {
            std::cout << "textura do jogador nao carregou" << std::endl;
        }
        if (!texturas[Menu].loadFromFile("assets/menu.png"))
        {
            std::cout << "textura do menu nao carregou" << std::endl;
        }
        if (!texturas[Guarda].loadFromFile("assets/guarda.png"))
        {
            std::cout << "textura do guarda nao carregou" << std::endl;
        }
    }

    Gerenciador_Grafico *Gerenciador_Grafico::getGerenciador_Grafico()
    {
        if (!pGrafico)
        {
            pGrafico = new Gerenciador_Grafico();
        }
        return pGrafico;
    }

    bool Gerenciador_Grafico::janelaAberta()
    {
        return window.isOpen();
    }

    sf::RenderWindow *Gerenciador_Grafico::getWindow()
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

    void Gerenciador_Grafico::desenhaEnte(Ente *pE)
    {
        if (pE)
        {
            sf::Sprite *pSprite = pE->getpSprite();
            if (pSprite)
            {
                window.draw(*pSprite);
            }

            sf::RectangleShape *pFig = pE->getpFig();
            if (pFig)
            {
                window.draw(*pFig);
            }
        }
    }

    void Gerenciador_Grafico::desenhaJanela()
    {
        if (window.isOpen())
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

    sf::Texture &Gerenciadores::Gerenciador_Grafico::getTextura(IDTextura id)
    {
        return texturas[id];
    }
}
