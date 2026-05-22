#include "entidades/Ente.hpp"
using namespace Gerenciadores;

int Ente::cont_id = 1;

Gerenciador_Grafico *Ente::pGG = NULL;

Ente::Ente() : id(cont_id++), pFig(NULL), textura()
{
    pFig = new sf::RectangleShape();

}

Ente::~Ente()
{
    if (pFig)
    {
        delete pFig;
        pFig = NULL;
    }
}

    void Ente::desenhar()
    {
        if (pGG)
        {
            pGG->desenhaEnte(this);
        }
    }

void Ente::setGG(Gerenciadores::Gerenciador_Grafico *pG)
{
    if (pG)
    {
        pGG = pG;
    }
}

sf::RectangleShape *Ente::getpFig()
{
    return pFig;
}