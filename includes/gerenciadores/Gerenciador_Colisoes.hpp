#pragma once
#include "Header.hpp"
#include "entidades/personagens/Jogador.hpp"
#include "entidades/personagens/Inimigo.hpp"
#include "entidades/Projetil.hpp"
#include "entidades/obstaculos/Obstaculo.hpp"

namespace Gerenciadores
{
    class Gerenciador_Colisoes
    {
    private:
        static Gerenciador_Colisoes *pColisao;
        std::vector<Entidades::Personagens::Inimigo *> LIs;
        std::list<Entidades::Obstaculos::Obstaculo *> LOs;
        std::set<Entidades::Projetil *> LPs;
        Entidades::Personagens::Jogador *pJog1;

    private:
        Gerenciador_Colisoes();

    public:
        ~Gerenciador_Colisoes();

        static Gerenciador_Colisoes *getGerenciador_Colisoes();
        void setJogador1(Entidades::Personagens::Jogador *pJ);
        void incluirInimigo(Entidades::Personagens::Inimigo *pi);
        void incluirObstaculo(Entidades::Obstaculos::Obstaculo *po);
        void incluirProjetil(Entidades::Projetil *pj);
        void executar();

    private:
        const bool verificarColisao(Entidades::Entidade *pe1, Entidades::Entidade *pe2) const;
        void tratarColisoesJogsObstacs();
        void tratarColisoesJogsInimgs();
        void tratarColisoesJogsProjeteis();
    };

}