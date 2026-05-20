#pragma once
#include "Header.hpp"
#include "entidades/Entidade.hpp"

namespace Entidades
{
    class Projetil : public Entidade
    {
    protected:
        bool ativo;

    public:
        Projetil(int posX = 0, int posY = 0, bool flag = true);
        ~Projetil();

        //void executar();
        //void salvar();
    };
}
