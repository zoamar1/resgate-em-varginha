#pragma once
#include "Header.hpp"
#include "Entidade.hpp"
#include "personagens/Jogador.hpp"

namespace Fases
{
    class Fase;
}

namespace Entidades
{
    class Portal : public Entidade
    {
    private:
        Fases::Fase *pFase;

    public:
        Portal(float posX = 0, float posY = 0, Fases::Fase *pFase = NULL);
        ~Portal();
        void executar();
        void salvar();
        void teleportar(Entidades::Personagens::Jogador *pJog);
    };
}