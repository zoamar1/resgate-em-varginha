#pragma once
#include "Header.hpp"
#include "entidades/Entidade.hpp"

namespace Entidades
{
    class Projetil : public Entidade
    {
    protected:
        bool ativo;
        int dano;

    public:
        Projetil(int posX = 0, int posY = 0, bool flag = true, int dano = 0);
        ~Projetil();

        bool getAtivo() const;
        bool getDano() const;

        // void executar();
        // void salvar();
    };
}
