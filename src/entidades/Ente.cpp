#include "entidades/Ente.hpp"
using namespace Gerenciadores;

int Ente::cont_id = 1;

Gerenciador_Grafico *Ente::pGG = NULL;

Ente::Ente() : id(cont_id++), pFig(NULL)
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

void Ente::aplicarTextura(Gerenciadores::IDTextura idTextura) {
    if (pGG != NULL && pFig != NULL) {
        sf::Texture* tex = &(pGG->getTextura(idTextura));
        pFig->setTexture(tex);
    }
        pFig->setOutlineColor(sf::Color::Green); 
        pFig->setOutlineThickness(1.0f);
}