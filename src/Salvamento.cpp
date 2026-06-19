#include "Salvamento.hpp"
#include "entidades/personagens/Jogador.hpp"


using json = nlohmann::json;

namespace
{
    const std::string ARQUIVO_SALVAMENTOS = "salvamentos.json";

    json carregarTudo()
    {
        json raiz = json::object();
        std::ifstream arquivo(ARQUIVO_SALVAMENTOS);
        if (arquivo.is_open())
        {
            try
            {
                arquivo >> raiz;
            }
            catch (...)
            {
                std::cerr << "Erro ao decodificar arquivo de salvamentos." << std::endl;
                raiz = json::object();
            }
        }
        return raiz;
    }

    void salvarTudo(const json &raiz)
    {
        std::ofstream arquivo(ARQUIVO_SALVAMENTOS);
        if (arquivo.is_open())
        {
            arquivo << raiz.dump(4);
        }
    }

    std::string montarChave(const std::string &nome1, const std::string &nome2, bool modo2)
    {
        if (modo2 && !nome2.empty())
        {
            return nome1 + "_&_" + nome2;
        }
        return nome1;
    }
}

void Salvamento::salvarJogo(Entidades::Personagens::Jogador *pJog1,
                            Entidades::Personagens::Jogador *pJog2,
                            bool modo2Jogadores,
                            int faseAtual,
                            const std::vector<std::string> &dadosCenario)
{
    if (!pJog1)
        return;

    pJog1->salvar();
    json dadosJ1 = json::parse(pJog1->getBufferDados());

    json registro;
    registro["modo2"] = modo2Jogadores;
    registro["fase"] = faseAtual;
    registro["jogador1"] = dadosJ1;

    if (modo2Jogadores && pJog2)
    {
        pJog2->salvar();
        registro["jogador2"] = json::parse(pJog2->getBufferDados());
    }
    else
    {
        registro["jogador2"] = nullptr;
    }

    json cenario = json::array();
    for (size_t i = 0; i < dadosCenario.size(); i++)
    {
        try
        {
            cenario.push_back(json::parse(dadosCenario[i]));
        }
        catch (...)
        {
        }
    }
    registro["cenario"] = cenario;

    std::string chave = montarChave(pJog1->getNome(), pJog2 ? pJog2->getNome() : "", modo2Jogadores);

    json raiz = carregarTudo();
    raiz[chave] = registro;
    salvarTudo(raiz);
}

bool Salvamento::carregarJogo(const std::string &chave,
                              Entidades::Personagens::Jogador *pJog1,
                              Entidades::Personagens::Jogador *pJog2,
                              bool &modo2Jogadores,
                              int &faseAtual)
{
    json raiz = carregarTudo();

    if (raiz.find(chave) == raiz.end())
        return false;

    json registro = raiz[chave];

    modo2Jogadores = registro.value("modo2", false);
    faseAtual = registro.value("fase", 1);

    if (pJog1 && registro.contains("jogador1") && !registro["jogador1"].is_null())
    {
        json j1 = registro["jogador1"];
        pJog1->setNome(j1.value("nome", pJog1->getNome()));
        pJog1->setPontos(j1.value("pontos", 0));
        pJog1->set_vida_atual(j1.value("vida_atual", pJog1->get_num_vidas()));
    }

    if (modo2Jogadores && pJog2 && registro.contains("jogador2") && !registro["jogador2"].is_null())
    {
        json j2 = registro["jogador2"];
        pJog2->setNome(j2.value("nome", pJog2->getNome()));
        pJog2->setPontos(j2.value("pontos", 0));
        pJog2->set_vida_atual(j2.value("vida_atual", pJog2->get_num_vidas()));
    }

    return true;
}

void Salvamento::removerJogo(const std::string &chave)
{
    json raiz = carregarTudo();
    if (raiz.find(chave) != raiz.end())
    {
        raiz.erase(chave);
        salvarTudo(raiz);
    }
}

std::vector<std::pair<std::string, std::string>> Salvamento::listarResumos()
{
    std::vector<std::pair<std::string, std::string>> resultado;
    json raiz = carregarTudo();

    for (json::iterator it = raiz.begin(); it != raiz.end(); ++it)
    {
        std::string chave = it.key();
        json registro = it.value();

        std::string nome1 = "?";
        int pontos1 = 0;
        if (registro.contains("jogador1") && !registro["jogador1"].is_null())
        {
            nome1 = registro["jogador1"].value("nome", "?");
            pontos1 = registro["jogador1"].value("pontos", 0);
        }

        bool modo2 = registro.value("modo2", false);
        int fase = registro.value("fase", 1);

        std::ostringstream ss;
        ss << nome1;

        if (modo2 && registro.contains("jogador2") && !registro["jogador2"].is_null())
        {
            std::string nome2 = registro["jogador2"].value("nome", "?");
            ss << " & " << nome2;
        }

        ss << "  -  Fase " << fase << "  -  " << pontos1 << " pts";

        resultado.push_back(std::make_pair(chave, ss.str()));
    }

    return resultado;
}

bool Salvamento::carregarJogo(const std::string &chave,
                              Entidades::Personagens::Jogador *pJog1,
                              Entidades::Personagens::Jogador *pJog2,
                              bool &modo2Jogadores,
                              int &faseAtual,
                              std::vector<std::string> &dadosCenario)
{
    json raiz = carregarTudo();

    if (raiz.find(chave) == raiz.end())
        return false;

    json registro = raiz[chave];

    modo2Jogadores = registro.value("modo2", false);
    faseAtual = registro.value("fase", 1);

    if (pJog1 && registro.contains("jogador1") && !registro["jogador1"].is_null())
    {
        json j1 = registro["jogador1"];
        pJog1->setNome(j1.value("nome", pJog1->getNome()));
        pJog1->setPontos(j1.value("pontos", 0));
        pJog1->set_vida_atual(j1.value("vida_atual", pJog1->get_num_vidas()));
    }

    if (modo2Jogadores && pJog2 && registro.contains("jogador2") && !registro["jogador2"].is_null())
    {
        json j2 = registro["jogador2"];
        pJog2->setNome(j2.value("nome", pJog2->getNome()));
        pJog2->setPontos(j2.value("pontos", 0));
        pJog2->set_vida_atual(j2.value("vida_atual", pJog2->get_num_vidas()));
    }

    dadosCenario.clear();
    if (registro.contains("cenario") && registro["cenario"].is_array())
    {
        for (auto &item : registro["cenario"])
        {
            dadosCenario.push_back(item.dump());
        }
    }

    return true;
}