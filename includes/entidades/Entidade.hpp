#pragma once
#include "Header.hpp"
#include "Ente.hpp"

namespace Entidades
{
    class Entidade : public Ente
    {
    protected:
        float x;
        float y;
        float vel_max;
        float velx;
        float vely;
        bool noChao;
        bool sofreEfeitoGravidade;
        static const float valor_gravidade;

        // ostream buffer;

    public:
        Entidade(float posX = 0.0f, float posY = 0.0f, float tamanhoX = 0.0f, float tamanhoY = 0.0f, bool noChao, bool sofreEfeitoGravidade, float velx = 0, float vely = 0);
        virtual ~Entidade();

        virtual void executar() = 0;
        virtual void salvar() = 0;

        void setPosicao(float posx, float posy);
        float getX() const;
        float getY() const;
        void setX(float posX);
        void setY(float posY);
        void setVelX(float x);
        void setVelY(float y);
        void setVel_Max(float max);
        float getVelX() const;
        float getVelY() const;
        float getVel_Max() const;
        // protected:
        // void salvarDataBuffer();

        void setNoChao(bool flag);
        bool getNoChao() const;
        void setSofreEfeitoGravidade(bool flag);
        void aplicarGravidade(float g = 0);
    };
}
