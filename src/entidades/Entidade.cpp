#include "entidades/Entidade.hpp"

namespace Entidades
{
    Entidade::Entidade(float posX, float posY, float tamanhoX, float tamanhoY) : Ente(),
                                                                                 x(posX), y(posY)
    {
        pFig->setSize({tamanhoX, tamanhoY});
        pFig->setOrigin({0.0f, 0.0f});
        pFig->setPosition({posX, posY});
    }

    Entidade::~Entidade()
    {
        x = -50;
        y = -50;
    }

    void Entidade::setPosicao(float posx, float posy)
    {
        x = posx;
        y = posy;
        pFig->setPosition({posx, posy});
    }
    float Entidade::getX() const
    {
        return x;
    }
    float Entidade::getY() const
    {
        return y;
    }

    void Entidade::setX(float posX)
    {
        x = posX;
        pFig->setPosition({x, y});
    }

    void Entidade::setY(float posY)
    {
        y = posY;
        pFig->setPosition({x, y});
    }
}
