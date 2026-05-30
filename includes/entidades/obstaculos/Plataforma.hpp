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
            float altura;

        public:
            Plataforma(float posX = 0.0f, float posY = 0.0f, float tamanhoX = 0.0f, float tamanhoY = 0.0f);
            ~Plataforma();
            void salvar();
            void executar(Entidades::Personagens::Jogador *p);
            void obstaculizar(Entidades::Personagens::Jogador *p);
        };
    }
}