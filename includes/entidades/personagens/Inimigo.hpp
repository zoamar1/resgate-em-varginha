#pragma once
#include "Header.hpp"
#include "Personagem.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;

        class Inimigo : public Personagem
        {
        protected:
            int nivel_maldade;

        public:
            // lembrar de mudar n(numero de vidas) para o padrao do INIMIGO!!!!
            Inimigo(float posX = 0.0f, float posY = 0.0f, int n = 3, int maldade = 0);
            virtual ~Inimigo();

            // void salvarDataBuffer();
            virtual void executar() = 0;
            virtual void danificar(Jogador *p) = 0;
            virtual void salva() = 0;
        };
    }
}
