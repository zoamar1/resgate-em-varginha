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
            Espinhos(int posX = 0, int posY = 0, int tamanhoX = 0, int tamanhoY = 0, short int dano = 0);
            ~Espinhos();
            void salvar();
            void executar(Entidades::Personagens::Jogador *p);
            void obstaculizar(Entidades::Personagens::Jogador *p);
        };
    }
}