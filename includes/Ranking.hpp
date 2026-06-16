#pragma once
#include <string>
#include <vector>
#include <utility>

class Ranking
{
public:
    static void salvar(const std::vector<std::pair<std::string, int>> &novasEntradas);

    static std::vector<std::pair<std::string, int>> carregar();
};