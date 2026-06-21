#pragma once
#include "fases/Fase.hpp"
#include "entidades/personagens/Exercito.hpp"

namespace Fases
{
    class FasePrimeira : public Fase
    {
    private:
        const int maxInimMedios;
        std::vector<sf::Vector2f> posicoesArbustos;
        std::vector<sf::Vector2f> posicoesInimigosMedios;
        std::vector<Entidades::Personagens::Exercito *> vetorExercitos;

    public:
        FasePrimeira(Gerenciadores::Gerenciador_Colisoes *pGC, const dC &dadosCenario = dC());
        ~FasePrimeira();
        void executar();

    protected:
        void criarInimMedios();
        void criarArbustos();
        void criarProjeteis();

        void criarInimigos();
        void criarObstaculo();

        void carregarInimigoEspecial(const std::string &dadoJson) override;
    };
}