#pragma once
#include "Header.hpp"
#include "entidades/Entidade.hpp"

namespace Entidades
{
    namespace Personagens
    {

        class Personagem : public Entidades::Entidade
        {
        protected:
            int num_vidas;
            //adicionar numero max de vidas

        public:
            Personagem(float posX = 0.0f, float posY = 0.0f, float tamanhoX = 0.0f, float tamanhoY = 0.0f, int n = 0);
            virtual ~Personagem();

            virtual void executar() = 0;
            virtual void salvar() = 0;
            virtual void mover() = 0;

            virtual void recebeDano(int dano = 0);

            void operator++();
        };
    }
}
