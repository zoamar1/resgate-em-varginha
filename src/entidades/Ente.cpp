#include "entidades/Ente.hpp"
using namespace Gerenciadores;

int Ente::cont_id = 1;

Gerenciador_Grafico *Ente::pGG = NULL;

Ente::Ente() : id(cont_id++), pFig(new sf::RectangleShape()), pSprite(new sf::Sprite())
{
}

Ente::~Ente()
{
    if (pFig)
    {
        delete pFig;
        pFig = NULL;
    }
    if (pSprite)
    {
        delete pSprite;
        pSprite = NULL;
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

sf::Sprite *Ente::getpSprite()
{

    return pSprite;
}

void Ente::aplicarTextura(Gerenciadores::IDTextura idTextura)
{
    if (pGG != NULL && pSprite != NULL)
    {
        sf::Texture *tex = &(pGG->getTextura(idTextura));
        pSprite->setTexture(*tex);

        if (pFig != NULL)
        {
            float largSprite = pSprite->getLocalBounds().width;
            float altSprite = pSprite->getLocalBounds().height;
            float largHitbox = pFig->getSize().x;
            float altHitbox = pFig->getSize().y;

            pSprite->setScale(largHitbox / largSprite, altHitbox / altSprite);
            pFig->setFillColor(sf::Color::Transparent);
        }
    }
}

int Ente::getId() const
{
    return id;
}