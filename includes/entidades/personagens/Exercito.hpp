#pragma once
#include "Header.hpp"
#include "Inimigo.hpp"
#include "entidades/Projetil.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;

        class Exercito : public Inimigo
        {
        protected:
            int raio;
            sf::Clock relogioExplosao;
            bool explodindo;

        public:
            Exercito(float posX = 0.0f, float posY = 0.0f, int n = 3, int maldade = 0, int r = 0);
            ~Exercito();

            void executar();
            void danificar(Jogador *p);
            void mover();
            void salvar();
            void atirar(Entidades::Projetil *pProjetil) override;
            void desenharExplosao();
            bool getExplodindo() const;
        };
    }
}