#pragma once
#include "Header.hpp"
#include "entidades/Entidade.hpp"

namespace Personagens
{
    class Personagem : public Entidade
    {
    protected:
        int num_vidas;

    public:
        Personagem(int posX = 0, int posY = 0, int n = 0);
        virtual ~Personagem();

        // void salvarDataBuffer();
        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void mover() = 0;
    };
}
