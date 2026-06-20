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
            Obstaculo(float posX = 0.0f, float posY = 0.0f, float tamanhoX = 0.0f, float tamanhoY = 0.0f, bool dano = false);
            virtual ~Obstaculo();
            void salvarDataBuffer() override;
            virtual void executar() = 0;
            virtual void salvar() = 0;
            virtual void obstaculizar(Entidades::Personagens::Jogador *p) = 0;
        };
    }
}