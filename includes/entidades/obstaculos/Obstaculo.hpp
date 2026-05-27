#pragma once
#include "Header.hpp"
#include "entidades/personagens/Jogador.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        class Obstaculo : public Entidade
        {
        protected:
            bool danoso;

        public:
            Obstaculo(int posX = 0, int posY = 0, int tamanhoX = 0, int tamanhoY = 0, bool danoso = false);
            virtual ~Obstaculo();
            void salvarDataBuffer();
            virtual void executar() = 0;
            virtual void salvar() = 0;
            virtual void obstaculizar(Entidades::Personagens::Jogador *p) = 0;
        };
    }
}