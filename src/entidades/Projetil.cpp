#include "entidades/Projetil.hpp"
#include "entidades/personagens/ET_Varginha.hpp"

namespace Entidades
{
    Projetil::Projetil(float posX, float posY, bool flag, int dano)
        : Entidade(sf::Vector2f(posX, posY), sf::Vector2f(0.0f, 0.0f)),
          ativo(flag),
          dano(dano),
          deJogador(false),
          pAlien(NULL),
          idDonoJogador(-1),
          idAlienDono(-1)
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
        pAlien = NULL;
    }

    bool Projetil::getAtivo() const
    {
        return ativo;
    }

    void Projetil::setAtivo(bool valor)
    {
        ativo = valor;
    }

    int Projetil::getDano() const
    {
        return dano;
    }

    bool Projetil::getDeJogador() const
    {
        return deJogador;
    }

    void Projetil::setDeJogador(bool valor)
    {
        deJogador = valor;
    }

    void Projetil::setpAlien(Personagens::ET_Varginha *pA)
    {
        if (pA)
        {
            pAlien = pA;
            idAlienDono = pA->getId();
            aplicarTextura(Gerenciadores::Projetil_Alien);
        }
        else
        {
            pAlien = NULL;
            idAlienDono = -1;
            aplicarTextura(Gerenciadores::Projetil);
        }
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
            setpAlien(NULL);
        }
    }

    void Projetil::executar()
    {
        if (ativo)
            mover();
        if (pAlien)
        {
            pFig->setFillColor(sf::Color::Red);
        }
    }

    void Projetil::salvar()
    {
        salvarDataBuffer();
        nlohmann::json j = nlohmann::json::parse(getBufferDados());
        j["tipo"] = "Projetil";
        j["dano"] = dano;
        j["ativo"] = ativo;
        j["deJogador"] = deJogador;
        j["idDonoJogador"] = idDonoJogador;
        j["idAlienDono"] = idAlienDono;
        escreverBuffer(j);
    }

    Personagens::ET_Varginha *Projetil::getpAlien() const 
    { 
        return pAlien; 
    }

    void Projetil::setIdDonoJogador(int idx) 
    { 
        idDonoJogador = idx; 
    }
    int Projetil::getIdDonoJogador() const 
    { 
        return idDonoJogador; 
    }
    int Projetil::getIdAlienDono() const 
    { 
        return idAlienDono; 
    }
}