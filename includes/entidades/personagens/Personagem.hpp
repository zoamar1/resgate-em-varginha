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
            Personagem(float posX = 0.0f, float posY = 0.0f, float tamanhoX = 0.0f, float tamanhoY = 0.0f, int n = 0);
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
