#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "entidades/Ente.hpp"

namespace Gerenciadores
{
    Gerenciador_Grafico *Gerenciador_Grafico::pGrafico = NULL;

    Gerenciador_Grafico::Gerenciador_Grafico() : window(sf::VideoMode(LARGURA, ALTURA), "Resgate em Varginha")
    {
        carregaTexturas();
        window.setFramerateLimit(60);
    }

    Gerenciador_Grafico::~Gerenciador_Grafico()
    {
        pGrafico = NULL;
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

    void Gerenciador_Grafico::desenhaTexto(sf::Text texto)
    {
        if (window.isOpen())
        {
            window.draw(texto);
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

            // rever essa parte

            /*sf::RectangleShape *pFig = pE->getpFig();
            if (pFig)
            {
                window.draw(*pFig);
            }*/
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

    void Gerenciador_Grafico::carregaTexturas()
    {
        texturas.resize(17);

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
        if (!texturas[Arbusto].loadFromFile("assets/arbusto.png"))
        {
            std::cout << "textura do guarda nao carregou" << std::endl;
        }
        if (!texturas[Chao].loadFromFile("assets/chao.png"))
        {
            std::cout << "textura do guarda nao carregou" << std::endl;
        }
        if (!texturas[Plataforma].loadFromFile("assets/plataforma.png"))
        {
            std::cout << "textura do guarda nao carregou" << std::endl;
        }
        if (!texturas[FundoFase1].loadFromFile("assets/fase1.png"))
        {
            std::cout << "textura do guarda nao carregou" << std::endl;
        }
        if (!texturas[FundoFase2].loadFromFile("assets/fase2.jpg"))
        {
            std::cout << "textura da fase 2 nao carregou" << std::endl;
        }
        if (!texturas[Exercito].loadFromFile("assets/exercito.png"))
        {
            std::cout << "textura do exercito nao carregou" << std::endl;
        }
        if (!texturas[Projetil].loadFromFile("assets/bala.png"))
        {
            std::cout << "textura do projetil nao carregou" << std::endl;
        }
        if (!texturas[Projetil_Alien].loadFromFile("assets/bala_alien.png"))
        {
            std::cout << "textura do projetil nao carregou" << std::endl;
        }
        if (!texturas[Espinhos].loadFromFile("assets/espinhos.png"))
        {
            std::cout << "textura do espinhos nao carregou" << std::endl;
        }
        if (!texturas[ET_Varginha].loadFromFile("assets/alien.png"))
        {
            std::cout << "textura do alien nao carregou" << std::endl;
        }
        if (!texturas[ET_Varginha_Estressado].loadFromFile("assets/alien_nervoso.png"))
        {
            std::cout << "textura do alien estressado nao carregou" << std::endl;
        }
        if (!texturas[Jogador2].loadFromFile("assets/jogador2.png"))
        {
            std::cout << "textura do jogador2 nao carregou" << std::endl;
        }
        if (!texturas[Explosao].loadFromFile("assets/explosao.png"))
        {
            std::cout << "textura do explosao nao carregou" << std::endl;
        }
        if(!texturas[Portal].loadFromFile("assets/portal.png")){
            std::cout << "textura do portal nao carregou" << std::endl;
        }
    }

    sf::Texture &Gerenciadores::Gerenciador_Grafico::getTextura(IDTextura id)
    {
        return texturas[id];
    }

}
