#pragma once
#include "Header.hpp"
#include "Personagem.hpp"
#include "entidades/personagens/Inimigo.hpp"
#include "entidades/Projetil.hpp"

namespace Gerenciadores
{
    class Gerenciador_Colisoes;
}

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
            std::string nome;
            bool confuso;
            sf::Clock relogioConfusao;
            float tempoConfusao;
            int indiceJogador;

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
            void setInvencivel(bool valor) { invencivel = valor; }

            void setNome(const std::string &n) { nome = n; }
            const std::string &getNome() const { return nome; }
            void adicionarPontos(int pts) { pontos += pts; }
            int getPontos() const { return pontos; }
            void setPontos(int pts) { pontos = pts; }

            void ficarConfuso();
            bool getConfuso();
            void setConfusoEstado(bool valor) { confuso = valor; }

            void setIndiceJogador(int idx) { indiceJogador = idx; }
            int getIndiceJogador() const { return indiceJogador; }
        };
    }
}