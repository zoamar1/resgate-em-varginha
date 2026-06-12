#pragma once
#include "Header.hpp"
#include "entidades/personagens/Jogador.hpp"
#include "entidades/personagens/Inimigo.hpp"
#include "entidades/Projetil.hpp"
#include "entidades/obstaculos/Obstaculo.hpp"
#include "entidades/Chao.hpp"
#include "entidades/personagens/Personagem.hpp"

namespace Gerenciadores
{
    class Gerenciador_Colisoes
    {
    private:
        static Gerenciador_Colisoes *pColisao;
        std::vector<Entidades::Personagens::Inimigo *> LIs;
        std::list<Entidades::Obstaculos::Obstaculo *> LOs;
        std::set<Entidades::Projetil *> LPs;
        std::vector<Entidades::Chao *> LCs;
        std::vector<Entidades::Personagens::Jogador *> LJs;

    private:
        Gerenciador_Colisoes();

    public:
        ~Gerenciador_Colisoes();

        static Gerenciador_Colisoes *getGerenciador_Colisoes();
        void incluirJogador(Entidades::Personagens::Jogador *pJ);
        void incluirInimigo(Entidades::Personagens::Inimigo *pi);
        void removerInimigo(Entidades::Personagens::Inimigo *pI);
        void incluirObstaculo(Entidades::Obstaculos::Obstaculo *po);
        void incluirChao(Entidades::Chao *pc);
        void incluirProjetil(Entidades::Projetil *pj);
        void executar();
        void limparTudo();

        void colisaoJogadorChao(Entidades::Chao *chao);
        void colisaoInimigoChao(Entidades::Chao *chao);

        const std::vector<Entidades::Personagens::Jogador *> &getJogadores() const;

    private:
        bool verificarColisao(Entidades::Entidade *pe1, Entidades::Entidade *pe2) const;
        void tratarColisoesJogsObstacs();
        void tratarColisoesJogsInimgs();
        void tratarColisoesJogsProjeteis();
        void tratarColisoesInimProjeteis();
    };
}