#include "entidades/Entidade.hpp"

namespace Entidades
{
    Entidade::Entidade(int posX, int posY, int tamanhoX, int tamanhoY) : 
    Ente(), 
    x(posX), y(posY)
    {
           pFig->setSize({(float)tamanhoX,(float)tamanhoY});

           pFig->setOrigin({(float)tamanhoX/2.0f, (float)tamanhoY/2.0f});
           pFig->setPosition({(float)posX, (float)posY});
    }

    Entidade::~Entidade()
    {
        x = -50;
        y = -50;
    }

    void Entidade::setPosicao(int posx, int posy)
    {
        x = posx;
        y = posy;
        pFig->setPosition({(float)posx,(float)posy});
    }
    int Entidade::getX() const
    {
        return x;
    }
    int Entidade::getY() const
    {
        return y;
    }
}
