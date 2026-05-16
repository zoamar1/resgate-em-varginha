#include "Jogo.hpp"

Jogo::Jogo() : 
pGG(Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()), pGE(Gerenciadores::Gerenciador_Eventos::getGerenciador_Eventos())
{
    pGE->setGerenciador_Grafico(pGG);
};

Jogo::~Jogo()
{
    pGG = NULL;
};

void Jogo::executar()
{
    if (pGG)
    {
        while (pGG->janelaAberta())
        {
            
            pGE->executar();
            pGG->getWindow()->clear(sf::Color::Black);

            pGG->getWindow()->display();
        }
    }
};