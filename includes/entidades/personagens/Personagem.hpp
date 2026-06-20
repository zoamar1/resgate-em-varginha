#pragma once
#include "Header.hpp"
#include "entidades/Entidade.hpp"

namespace Entidades
{
    class Projetil;
}

namespace Entidades
{
    namespace Personagens
    {
        class Personagem : public Entidades::Entidade
        {
        protected:
            const int num_vidas;
            int vida_atual;

            void salvarDataBuffer() override;

        public:
            Personagem(float posX = 0.0f, float posY = 0.0f, float tamanhoX = 0.0f, float tamanhoY = 0.0f, int n = 0);
            virtual ~Personagem();

            virtual void executar() = 0;
            virtual void salvar() = 0;
            virtual void mover() = 0;
            virtual void recebeDano(int dano = 0);
            int get_vida_atual() const;
            void set_vida_atual(int vida);
            virtual int get_num_vidas() const;
            void operator++();
        };
    }
}