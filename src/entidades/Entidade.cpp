#include "entidades/Entidade.hpp"

namespace Entidades
{
    const float Entidade::valor_gravidade = 1.0f;

    Entidade::Entidade(const sf::Vector2f &posicao, const sf::Vector2f &tamanho)
        : Ente(),
          posicao(posicao),
          vel_max(0.0f),
          velocidade(0.0f, 0.0f),
          noChao(false)
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

    void Entidade::setTamanho(const sf::Vector2f &tamanho)
    {
        if (pFig)
        {
            pFig->setSize(tamanho);
        }

        if (pSprite && pSprite->getTexture() && pFig)
        {
            float largSprite = pSprite->getLocalBounds().width;
            float altSprite = pSprite->getLocalBounds().height;
            if (largSprite > 0.0f && altSprite > 0.0f)
            {
                pSprite->setScale(tamanho.x / largSprite, tamanho.y / altSprite);
            }
        }
    }

    sf::Vector2f Entidade::getTamanho() const
    {
        if (pFig)
        {
            return pFig->getSize();
        }

        return sf::Vector2f(0.0f, 0.0f);
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

    void Entidade::setPosicao(float posx, float posy)
    {
        setPosicao(sf::Vector2f(posx, posy));
    }

    void Entidade::setVel_Max(float max)
    {
        vel_max = max;
    }

    float Entidade::getVel_Max() const
    {
        return vel_max;
    }

    void Entidade::aplicarGravidade()
    {
        if (!noChao)
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

    void Entidade::atualizarPosicao()
    {
        sf::Vector2f deslocamento = getVelocidade();

        if (deslocamento.x != 0.0f || deslocamento.y != 0.0f)
        {
            setPosicao(getPosicao() + deslocamento);
        }
    }

    void Entidade::anularGravidade()
    {
        velocidade.y -= valor_gravidade;
    }
}
