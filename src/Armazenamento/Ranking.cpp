#include "Armazenamento/Ranking.hpp"

using json = nlohmann::json;
const std::string Armazenamento::Ranking::caminhoArquivo = "ranking.json";

namespace Armazenamento
{
    void Ranking::salvar(const std::vector<std::pair<std::string, int>> &novasEntradas)
    {
        std::vector<std::pair<std::string, int>> rankingAtual = carregar();

        for (size_t i = 0; i < novasEntradas.size(); i++)
        {
            rankingAtual.push_back(novasEntradas[i]);
        }

        std::sort(rankingAtual.begin(), rankingAtual.end(),
                  [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
                  {
                      return a.second > b.second;
                  });

        json j = json::array();
        for (size_t i = 0; i < rankingAtual.size(); i++)
        {
            j.push_back({{"nome", rankingAtual[i].first}, {"pontuacao", rankingAtual[i].second}});
        }

        std::ofstream arquivo(caminhoArquivo);
        if (arquivo.is_open())
        {
            arquivo << j.dump(4);
            arquivo.close();
        }
    }

    std::vector<std::pair<std::string, int>> Ranking::carregar()
    {
        std::vector<std::pair<std::string, int>> entradas;
        std::ifstream arquivo(caminhoArquivo);

        if (!arquivo.is_open())
        {
            return entradas;
        }

        try
        {
            json j;
            arquivo >> j;
            arquivo.close();

            for (auto &item : j)
            {
                std::string nome = item.value("nome", "Desconhecido");
                int pontuacao = item.value("pontuacao", 0);
                entradas.push_back(std::make_pair(nome, pontuacao));
            }
        }
        catch (...)
        {
            std::cerr << "Erro ao decodificar arquivo JSON de ranking." << std::endl;
        }

        std::sort(entradas.begin(), entradas.end(),
                  [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
                  {
                      return a.second > b.second;
                  });

        return entradas;
    }
}
