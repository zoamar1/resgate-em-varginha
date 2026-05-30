#pragma once
#include "Header.hpp"
#include "entidades/obstaculos/Obstaculo.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        class Arbusto : public Obstaculo
        {
        private:
            int largura;

        public:
            Arbusto(int posX = 0, int posY = 0, int tamanhoX = 0, int tamanhoY = 0);
            ~Arbusto();
            void salvar();
            void executar(Entidades::Personagens::Jogador *p);
            void obstaculizar(Entidades::Personagens::Jogador *p);
        };
    }
}