#pragma once
#include "Header.hpp"
#include "Ente.hpp"
// using namespace std;

namespace Entidades
{
    class Entidade : public Ente
    {
    protected:
        int x;
        int y;

        // ostream buffer;

    public:
        Entidade(int posX = 0, int posY = 0, int tamanhoX = 0, int tamanhoY = 0);
        virtual ~Entidade();

        virtual void executar() = 0;
        virtual void salvar() = 0;

        void setPosicao(int posx, int posy);
        int getX() const;
        int getY() const;
        // protected:
        // void salvarDataBuffer();
    };
}
