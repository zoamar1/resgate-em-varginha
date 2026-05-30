#pragma once
#include "Header.hpp"
#include "Inimigo.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;

        class Guarda : public Inimigo
        {
        protected:
            int forca;

        public:
            Guarda(float posX = 0.0f, float posY = 0.0f, int n = 3, int maldade = 0, int f = 0);
            ~Guarda();

            // void salvarDataBuffer();
            void executar();
            void danificar(Jogador *p);
        };
    }
}
