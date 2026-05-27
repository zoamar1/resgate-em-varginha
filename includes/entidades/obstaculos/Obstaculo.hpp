#pragma once
#include "Header.hpp"
#include "entidades/personagens/Jogador.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        class Obstaculo
        {
        protected:
            bool danoso;

        public:
            Obstaculo();
            virtual ~Obstaculo();
            void salvarDataBuffer();
            virtual void executar() = 0;
            virtual void salvar() = 0;
            virtual void obstaculizar(Entidades::Personagens::Jogador *p) = 0;
        };
    }
}