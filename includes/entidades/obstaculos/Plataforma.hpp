#pragma once
#include "Header.hpp"
#include "entidades/obstaculos/Obstaculo.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        class Plataforma : public Obstaculo
        {
        private:
            int altura;

        public:
            Plataforma(int posX = 0, int posY = 0, int tamanhoX = 0, int tamanhoY = 0);
            ~Plataforma();
            void salvar();
            void executar(Entidades::Personagens::Jogador *p);
            void obstaculizar(Entidades::Personagens::Jogador *p);
        };
    }
}