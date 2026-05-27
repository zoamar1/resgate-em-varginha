#pragma once
#include "Header.hpp"
#include "entidades/personagens/Jogador.hpp"
#include "entidades/personagens/Inimigo.hpp"
#include "entidades/Projetil.hpp"

namespace Gerenciadores
{
    class Gerenciador_Colisoes
    {
    private:
        std::vector<Entidades::Personagens::Inimigo *> LIs;
        std::set<Entidades::Projetil *> LPs;
        Entidades::Personagens::Jogador *pJog1;

    public:
        Gerenciador_Colisoes();
        ~Gerenciador_Colisoes();

        void incluirInimigo(Entidades::Personagens::Inimigo *pi);
        // void incluirObstaculo(Entidades::Obstaculos::Obstaculo *po);
        void incluirProjetil(Entidades::Projetil *pj);
        void executar();

    private:
        const bool verificarColisao(Entidades::Entidade *pe1, Entidades::Entidade *pe2) const;
        void tratarColisoesJogsObstacs();
        void tratarColisoesJogsInimgs();
        void tratarColisoesJogsProjeteis();
    };

}