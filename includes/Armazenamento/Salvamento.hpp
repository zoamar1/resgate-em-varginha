#pragma once
#include "Header.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;
    }
}

namespace Armazenamento
{
    class Salvamento
    {
    private:
        static dC cenarioAtual;

    public:
        static void salvarJogo(Entidades::Personagens::Jogador *pJog1,
                               Entidades::Personagens::Jogador *pJog2,
                               bool modo2Jogadores,
                               int faseAtual,
                               const dC &dadosCenario);

        static bool carregarJogo(const std::string &chave,
                                 Entidades::Personagens::Jogador *pJog1,
                                 Entidades::Personagens::Jogador *pJog2,
                                 bool &modo2Jogadores,
                                 int &faseAtual);

        static void removerJogo(const std::string &chave);

        static bool carregarJogo(const std::string &chave,
                                 Entidades::Personagens::Jogador *pJog1,
                                 Entidades::Personagens::Jogador *pJog2,
                                 bool &modo2Jogadores,
                                 int &faseAtual,
                                 dC &dadosCenario);

        static std::vector<std::pair<std::string, std::string>> listarResumos();

        static const dC& getCenarioAtual() { return cenarioAtual; }
    };
}
