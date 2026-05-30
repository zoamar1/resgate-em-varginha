#pragma once
#include "Header.hpp"
#include "Inimigo.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;

        class Exercito : public Inimigo
        {
        protected:
            int precisao;

        public:
            Exercito(int posX = 0, int posY = 0, int n = 3, int maldade = 0, int p = 0);
            ~Exercito();

            // void salvarDataBuffer();
            void executar();
            void danificar(Jogador *p);
        };
    }
}
