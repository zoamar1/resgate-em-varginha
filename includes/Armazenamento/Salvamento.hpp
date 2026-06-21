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
    public:
        static void salvarJogo(Entidades::Personagens::Jogador *pJog1,
                               Entidades::Personagens::Jogador *pJog2,
                               bool modo2Jogadores,
                               int faseAtual,
                               const std::vector<std::string> &dadosCenario);

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
                                 std::vector<std::string> &dadosCenario);

        static std::vector<std::pair<std::string, std::string>> listarResumos();
    };
}
