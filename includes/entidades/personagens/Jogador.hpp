#pragma once
#include "Header.hpp"
#include "Personagem.hpp"
#include "entidades/personagens/Inimigo.hpp"
#include "entidades/Projetil.hpp"

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
            sf::Clock clockInvencivel;
            float tempoInvencivel;
            bool invencivel;
            sf::Clock relogioTiro;
            float cooldownTiros;

        public:
            Jogador(int n = 3, int p = 0, float tInvencivel = 1.0f, bool invencivel = false);
            ~Jogador();

            void colidir(Entidades::Personagens::Inimigo *pI);
            void executar();
            void salvar();
            void mover();

            void atirar(Entidades::Projetil *pProjetil);

            void pular();
            void setDirecao(int num);
            int getDirecao() const;
            void atualizarInvencibilidade();
            bool getInvencivel() const;
        };
    }
}