#pragma once
#include "fases/Fase.hpp"

namespace Fases
{
    class FaseSegunda : public Fase
    {
    private:
        const int maxETs;
        std::vector<sf::Vector2f> posicoesEspinhos;
        std::vector<sf::Vector2f> posicoesChefao;

    public:
        FaseSegunda(Gerenciadores::Gerenciador_Colisoes *pGC);
        ~FaseSegunda();
        void executar();

    protected:
        void criarEspinhos();
        void criarProjeteis();
        void criaChefao();

        void criarInimigos();
        void criarObstaculo();
    };
}