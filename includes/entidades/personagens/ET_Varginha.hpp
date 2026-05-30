#pragma once
#include "Header.hpp"
#include "Inimigo.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;

        class ET_Varginha : public Inimigo
        {
        protected:
            int multiplicador_laser;

        public:
            ET_Varginha(float posX = 0.0f, float posY = 0.0f, int n = 3, int maldade = 0, int ml = 0);
            ~ET_Varginha();

            // void salvarDataBuffer();
            void executar();
            void danificar(Jogador *p);
        };
    }
}
