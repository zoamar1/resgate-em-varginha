#include "entidades/Entidade.hpp"

namespace Entidades
{
    const float Entidade::valor_gravidade = 1.0f;

    Entidade::Entidade(const sf::Vector2f &posicao, const sf::Vector2f &tamanho, bool sofreGravidade)
        : Ente(),
          posicao(posicao),
          vel_max(0.0f),
          velocidade(0.0f, 0.0f),
          noChao(false),
          sofreEfeitoGravidade(sofreGravidade)
    {
        pFig->setSize(tamanho);
        pFig->setOrigin({0.0f, 0.0f});
        pFig->setPosition(posicao);

        if (pSprite)
        {
            pSprite->setPosition(posicao);
        }
    }

    Entidade::~Entidade()
    {
        posicao = sf::Vector2f(-50.0f, -50.0f);
    }

    sf::Vector2f Entidade::getPosicao() const
    {
        return posicao;
    }

    sf::Vector2f Entidade::getVelocidade() const
    {
        return velocidade;
    }

    void Entidade::setPosicao(const sf::Vector2f &posicao)
    {
        this->posicao = posicao;
        pFig->setPosition(posicao);
        if (pSprite)
            pSprite->setPosition(posicao);
    }

    void Entidade::setVelocidade(const sf::Vector2f &velocidade)
    {
        this->velocidade = velocidade;
    }

    float Entidade::getX() const
    {
        return posicao.x;
    }

    float Entidade::getY() const
    {
        return posicao.y;
    }

    void Entidade::setPosicao(float posx, float posy)
    {
        setPosicao(sf::Vector2f(posx, posy));
    }

    void Entidade::setX(float posX)
    {
        setPosicao(sf::Vector2f(posX, posicao.y));
    }

    void Entidade::setY(float posY)
    {
        setPosicao(sf::Vector2f(posicao.x, posY));
    }

    void Entidade::setVelX(float x)
    {
        velocidade.x = x;
    }

    void Entidade::setVelY(float y)
    {
        velocidade.y = y;
    }

    void Entidade::setVel_Max(float max)
    {
        vel_max = max;
    }

    float Entidade::getVelX() const
    {
        return velocidade.x;
    }

    float Entidade::getVelY() const
    {
        return velocidade.y;
    }

    float Entidade::getVel_Max() const
    {
        return vel_max;
    }

    void Entidade::aplicarGravidade()
    {
        if (sofreEfeitoGravidade && !noChao)
        {
            velocidade.y += valor_gravidade;
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
        sofreEfeitoGravidade = flag;
    }
}
