#pragma once
#include "Header.hpp"
#include "Inimigo.hpp"
#include "entidades/Projetil.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;

        class ET_Varginha : public Inimigo
        {
        protected:
            int multiplicador_forca;
            sf::Clock relogioTiro;
            float cooldownTiros;
            bool querAtirar;
            static Jogador *pJogador;
            std::vector<Projetil *> vetorProjeteis;
            bool estressado;
            sf::Clock relogioTeleporte;

        public:
            ET_Varginha(float posX = 0.0f, float posY = 0.0f, int n = 3, int maldade = 0, int ml = 0);
            ~ET_Varginha();

            void mover();
            void salvar();
            void executar();
            void danificar(Jogador *p);
            bool verificaPlayerArea();
            bool getQuerAtirar();
            std::vector<Projetil *> *getVetorProjeteis();
            void atirar(Entidades::Projetil *pProjetil);
            int get_num_vidas() const override;
        };
    }
}
