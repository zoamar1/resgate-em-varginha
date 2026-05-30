#pragma once
#include "Header.hpp"
#include "Ente.hpp"
// using namespace std;

namespace Entidades
{
    class Entidade : public Ente
    {
    protected:
        float x;
        float y;

        // ostream buffer;

    public:
        Entidade(float posX = 0.0f, float posY = 0.0f, float tamanhoX = 0.0f, float tamanhoY = 0.0f);
        virtual ~Entidade();

        virtual void executar() = 0;
        virtual void salvar() = 0;

        void setPosicao(float posx, float posy);
        float getX() const;
        float getY() const;
        void setX(float posX);
        void setY(float posY);
        // protected:
        // void salvarDataBuffer();
    };
}
