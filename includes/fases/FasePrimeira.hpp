#pragma once
#include "fases/Fase.hpp"

namespace Fases
{
    class FasePrimeira : public Fase
    {
    private:
        const int maxInimMedios;
        std::vector<sf::Vector2f> posicoesArbustos;
        std::vector<sf::Vector2f> posicoesInimigosMedios;

    public:
        FasePrimeira(Gerenciadores::Gerenciador_Colisoes *pGC);
        ~FasePrimeira();

    protected:
        void criarInimMedios();
        void criarArbustos();
        void criarProjeteis();

        void criarInimigos();
        void criarObstaculo();
    };
}