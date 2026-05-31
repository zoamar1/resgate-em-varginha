#pragma once
#include "Header.hpp"
#include "Personagem.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Inimigo;

        class Jogador : public Personagem
        {
        protected:
            int pontos;
            int direcao;
            sf::Clock relogioTiro;
            float tempoRecarga;
        public:
            // lembrar de mudar n(numero de vidas) para o padrao do jogador!!!!
            Jogador(float posX = 0.0f, float posY = 0.0f, int n = 3, int p = 0);
            ~Jogador();

            void executar();
            void salvar();
            void mover();
            void atirar();
            void setDirecao(int num);
            int getDirecao() const;
        };
    }
}