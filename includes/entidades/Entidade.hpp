#pragma once
#include "Header.hpp"
#include "Ente.hpp"

namespace Entidades
{
    class Entidade : public Ente
    {
    protected:
        sf::Vector2f posicao;
        float vel_max;
        sf::Vector2f velocidade;
        bool noChao;
        static const float valor_gravidade;

        std::ostringstream bufferDados;

        void escreverBuffer(const nlohmann::json &j);

    public:
        Entidade(const sf::Vector2f &posicao = {0, 0}, const sf::Vector2f &tamanho = {0, 0});
        virtual ~Entidade();

        virtual void executar() = 0;
        virtual void salvar() = 0;

        void setPosicao(const sf::Vector2f &posicao);
        sf::Vector2f getPosicao() const;
        void setTamanho(const sf::Vector2f &tamanho);
        sf::Vector2f getTamanho() const;
        void setVelocidade(const sf::Vector2f &velocidade);
        sf::Vector2f getVelocidade() const;

        void setPosicao(float posx, float posy);
        void setVel_Max(float max);
        float getVel_Max() const;

        void setNoChao(bool flag);
        bool getNoChao() const;
        void aplicarGravidade();
        virtual void atualizarPosicao();
        virtual void anularGravidade();

        virtual void salvarDataBuffer();
        std::string getBufferDados() const;
    };
}