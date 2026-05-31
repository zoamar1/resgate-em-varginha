#include "entidades/Entidade.hpp"

namespace Entidades
{
    const float Entidade::valor_gravidade = 4.2f;

    Entidade::Entidade(float posX, float posY, float tamanhoX, float tamanhoY) : Ente(), x(posX), y(posY), 
    {
        vel_max = 0.0f;
        velx = 0.0f;
        vely = 0.0f;

        pFig->setSize({tamanhoX, tamanhoY});
        pFig->setOrigin({0.0f, 0.0f});
        pFig->setPosition({posX, posY});

        if (pSprite)
        {
            pSprite->setPosition({posX, posY});
        }
    }

    Entidade::~Entidade()
    {
        x = -50;
        y = -50;
    }
    float Entidade::getX() const
    {
        return x;
    }
    float Entidade::getY() const
    {
        return y;
    }

    void Entidade::setPosicao(float posx, float posy)
    {
        x = posx;
        y = posy;
        pFig->setPosition({posx, posy});
        if (pSprite)
            pSprite->setPosition({posx, posy});
    }

    void Entidade::setX(float posX)
    {
        x = posX;
        pFig->setPosition({x, y});
        if (pSprite)
            pSprite->setPosition({x, y});
    }

    void Entidade::setY(float posY)
    {
        y = posY;
        pFig->setPosition({x, y});
        if (pSprite)
            pSprite->setPosition({x, y});
    }

    void Entidade::setVelX(float x)
    {
        velx = x;
    }

    void Entidade::setVelY(float y)
    {
        vely = y;
    }

    void Entidade::setVel_Max(float max)
    {
        vel_max = max;
    }

    float Entidade::getVelX() const
    {
        return velx;
    }

    float Entidade::getVelY() const
    {
        return vely;
    }

    float Entidade::getVel_Max() const
    {
        return vel_max;
    }

    void Entidade::aplicarGravidade(float dt)
    {
        if (temGravidade && !noChao)
        {
            velY += GRAVIDADE * dt;
            y += velY * dt;
            pFig->setPosition(x, y);
        }
    }

    void Entidade::setNoChao(bool flag)
    {
        noChao = flag;
    }

    bool Entidade::getNoChao() const
    {
        return noChao;
    }

    void Entidade::setSofreEfeitoGravidade(bool flag)
    {
        sofreEfeitoGravidad = flag;
    }
}
