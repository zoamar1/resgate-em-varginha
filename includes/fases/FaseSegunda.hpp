#pragma once
#include "fases/Fase.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class ET_Varginha;
    }
}

namespace Fases
{
    class FaseSegunda : public Fase
    {
    private:
        const int maxETs;
        std::vector<sf::Vector2f> posicoesEspinhos;
        std::vector<sf::Vector2f> posicoesChefao;
        std::vector<Entidades::Personagens::ET_Varginha *> vetorETs;
        std::map<int, Entidades::Personagens::ET_Varginha *> mapaAliensPorIdSalvo;

    public:
        FaseSegunda(Gerenciadores::Gerenciador_Colisoes *pGC, const dC &dadosCenario = dC());
        ~FaseSegunda();
        void executar();

    protected:
        void criarEspinhos();
        void criarProjeteis();
        void criaChefao();

        void criarInimigos();
        void criarObstaculo();

        void carregarInimigoEspecial(const std::string &dadoJson) override;
        void relacionarProjetilAlien(Entidades::Projetil *pProj, int idAlienSalvo) override;
    };
}