#pragma once
#include "Header.hpp"
#include "Personagem.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;

        class Inimigo : public Personagem
        {
        protected:
            int nivel_maldade;
            sf::Vector2f posicaoInicial;

            void salvarDataBuffer() override;

        public:
            Inimigo(float posX = 0.0f, float posY = 0.0f, int n = 3, int maldade = 0);
            virtual ~Inimigo();

            virtual void salvar() = 0;
            virtual void executar() = 0;
            virtual void danificar(Jogador *p) = 0;

            void setPosicaoInicial(const sf::Vector2f &pos);
            sf::Vector2f getPosicaoInicial() const;
        };
    }
}