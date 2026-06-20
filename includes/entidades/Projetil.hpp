#pragma once
#include "Header.hpp"
#include "entidades/Entidade.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class ET_Varginha;
    }

    class Projetil : public Entidade
    {
    protected:
        bool ativo;
        int dano;
        bool deJogador;
        Personagens::ET_Varginha *pAlien;
        int idDonoJogador;
        int idAlienDono;

    public:
        Projetil(float posX = 0.0f, float posY = 0.0f, bool flag = true, int dano = 0);
        ~Projetil();

        bool getAtivo() const;
        void setAtivo(bool valor);
        int getDano() const;
        bool getDeJogador() const;
        void setDeJogador(bool valor);
        void setpAlien(Personagens::ET_Varginha *pA);
        Personagens::ET_Varginha *getpAlien() const { return pAlien; }
        void setIdDonoJogador(int idx) { idDonoJogador = idx; }
        int getIdDonoJogador() const { return idDonoJogador; }
        int getIdAlienDono() const { return idAlienDono; }
        void mover();
        void executar();
        void salvar();
    };
}