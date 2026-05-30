#pragma once
#include "Header.hpp"
#include "entidades/obstaculos/Obstaculo.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        class Espinhos : public Obstaculo
        {
        private:
            short int danosidade;

        public:
            Espinhos(float posX = 0.0f, float posY = 0.0f, float tamanhoX = 0.0f, float tamanhoY = 0.0f, short int dano = 0);
            ~Espinhos();
            void salvar();
            void executar(Entidades::Personagens::Jogador *p);
            void obstaculizar(Entidades::Personagens::Jogador *p);
        };
    }
}