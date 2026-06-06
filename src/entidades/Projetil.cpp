#include "entidades/Projetil.hpp"

namespace Entidades
{
    Projetil::Projetil(float posX, float posY, bool flag, int dano)
        : Entidade(sf::Vector2f(posX, posY), sf::Vector2f(0.0f, 0.0f)),
          ativo(flag),
          dano(dano),
          pDono(NULL)
    {
        if (pFig)
        {
            setTamanho(sf::Vector2f(40.0f, 20.0f));
            pFig->setFillColor(sf::Color::Yellow);
            pFig->setPosition(getPosicao());
            setVelocidade({10.0f, 0.0f});
            setVel_Max(10.0f);
        }

        aplicarTextura(Gerenciadores::Projetil);
    }

    Projetil::~Projetil()
    {
    }

    bool Projetil::getAtivo() const
    {
        return ativo;
    }

    void Projetil::setAtivo(bool valor)
    {
        ativo = valor;
    }

    bool Projetil::getDano() const
    {
        return dano;
    }

    void Projetil::setDono(Entidades::Entidade *pE)
    {
        pDono = pE;
    }

    void Projetil::mover()
    {
        aplicarGravidade();
        anularGravidade();

        sf::Vector2f deslocamento = getVelocidade();

        if (deslocamento.x != 0.0f || deslocamento.y != 0.0f)
        {
            setPosicao(getPosicao() + deslocamento);
        }

        sf::Vector2f pos = getPosicao();
        if (pos.x < -100.0f || pos.x > LARGURA + 100.0f ||
            pos.y < -100.0f || pos.y > ALTURA + 100.0f)
        {
            setAtivo(false);
            setPosicao(sf::Vector2f(-500.0f, -500.0f));
            setVelocidade(sf::Vector2f(0.0f, 0.0f));
        }
    }

    void Projetil::executar()
    {
        if (ativo)
            mover();
    }

    void Projetil::salvar()
    {
    }

    Entidades::Entidade *Projetil::getDono()
    {
        return pDono;
    }
}