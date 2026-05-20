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
        Entidade(int posX = 0, int posY = 0);
        virtual ~Entidade();

        virtual void executar() = 0;
        virtual void salvar() = 0;

        // protected:
        // void salvarDataBuffer();
    };
}
