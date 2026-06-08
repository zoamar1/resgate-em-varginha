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
        bool deJogador;

    public:
        Projetil(float posX = 0.0f, float posY = 0.0f, bool flag = true, int dano = 0);
        ~Projetil();

        bool getAtivo() const;
        void setAtivo(bool valor);
        int getDano() const;
        bool getDeJogador() const;
        void setDeJogador(bool valor);
        void mover();
        void executar();
        void salvar();
    };
}