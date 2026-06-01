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
        Entidades::Entidade *pDono;
    public:
        Projetil(float posX = 0.0f, float posY = 0.0f, bool flag = true, int dano = 0);
        ~Projetil();

        bool getAtivo() const;
        bool getDano() const;
        Entidades::Entidade* getDono();
        void mover();
        void executar();
        void salvar();
    };
}
