#pragma once
#include "Header.hpp"

namespace Armazenamento
{
    class Ranking
    {
    private:
        static const std::string caminhoArquivo;

    public:
        static void salvar(const std::vector<std::pair<std::string, int>> &novasEntradas);

        static std::vector<std::pair<std::string, int>> carregar();
    };
}
