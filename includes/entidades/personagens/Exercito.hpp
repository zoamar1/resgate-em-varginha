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
            int raio;
            sf::Vector2f posicaoInicial;

        public:
            Exercito(float posX = 0.0f, float posY = 0.0f, int n = 3, int maldade = 0, int r = 0);
            ~Exercito();

            // void salvarDataBuffer();
            void executar();
            void danificar(Jogador *p);
            void mover();
            void salva();
            void atirar();
            int verificaPlayerArea();
        };
    }
}
