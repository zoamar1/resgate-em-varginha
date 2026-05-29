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
            float vel_max;
            float velx;
            float vely;

        public:
            Personagem(int posX = 0, int posY = 0, int tamanhoX = 0, int tamanhoY = 0, int n = 0);
            virtual ~Personagem();

            // void salvarDataBuffer();
            void setVelX(float x);
            void setVelY(float y);
            void setVel_Max(float max);
            float getVelX() const;
            float getVelY() const;
            float getVel_Max() const;

            virtual void executar() = 0;
            virtual void salvar() = 0;
            virtual void mover() = 0;

            virtual void recebeDano(int dano = 0);
        };
    }
}
