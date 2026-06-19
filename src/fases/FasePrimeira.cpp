#include "fases/FasePrimeira.hpp"
#include "entidades/obstaculos/Arbusto.hpp"
#include "entidades/personagens/Exercito.hpp"
#include "entidades/personagens/ET_Varginha.hpp"

namespace Fases
{

    FasePrimeira::FasePrimeira(Gerenciadores::Gerenciador_Colisoes *pGC,
                               const std::vector<std::string> &dadosCenario)
        : Fase(pGC), maxInimMedios(50)
    {
        pFig->setSize({LARGURA - 1, ALTURA - 1});
        pFig->setOrigin({0, 0});
        aplicarTextura(Gerenciadores::FundoFase1);

        if (dadosCenario.empty())
            criarCenario();
        else
            carregarCenario(dadosCenario);
    }

    void FasePrimeira::carregarInimigoEspecial(const std::string &dadoJson)
    {
        try
        {
            nlohmann::json j = nlohmann::json::parse(dadoJson);
            if (j.value("tipo", "") != "Exercito")
                return;

            int vidaAtual = j.value("vida_atual", 0);
            if (vidaAtual <= 0)
                return;

            float posX = j.value("posX", 0.0f);
            float posY = j.value("posY", 0.0f);
            int numVidas = j.value("num_vidas", 3);
            int raio = j.value("raio", 400);

            Entidades::Personagens::Exercito *pExercito =
                new Entidades::Personagens::Exercito(posX, posY, numVidas, 15, raio);
            pExercito->set_vida_atual(vidaAtual);

            lista_ents.incluir(static_cast<Entidades::Entidade *>(pExercito));
            vetorExercitos.push_back(pExercito);

            if (GC)
                GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo *>(pExercito));
        }
        catch (...)
        {
            std::cerr << "Erro ao carregar Exercito salvo." << std::endl;
        }
    }

    FasePrimeira::~FasePrimeira()
    {
        posicoesInimigosMedios.clear();
        vetorExercitos.clear();
        posicoesArbustos.clear();
    }

    void FasePrimeira::executar()
    {
        Fase::executar();

        for (auto it = vetorExercitos.begin(); it != vetorExercitos.end();)
        {
            if (*it == NULL || (*it)->get_vida_atual() <= 0)
            {
                it = vetorExercitos.erase(it);
            }
            else
            {
                it++;
            }
        }

        lista_ents.removerMortos(GC);
    }

    void FasePrimeira::criarInimMedios()
    {
        posicoesInimigosMedios.clear();
        posicoesInimigosMedios.push_back(sf::Vector2f(100.0f, 863.0f));
        posicoesInimigosMedios.push_back(sf::Vector2f(700.0f, 863.0f));
        posicoesInimigosMedios.push_back(sf::Vector2f(1200.0f, 863.0f));
        posicoesInimigosMedios.push_back(sf::Vector2f(200.0f, 493.0f));
        posicoesInimigosMedios.push_back(sf::Vector2f(1100.0f, 493.0f));
        posicoesInimigosMedios.push_back(sf::Vector2f(450.0f, 123.0f));
        posicoesInimigosMedios.push_back(sf::Vector2f(600.0f, 123.0f));
        posicoesInimigosMedios.push_back(sf::Vector2f(1100.0f, 123.0f));

        int quantidade = (rand() % 3) + 3;

        for (int i = 0; i < quantidade; i++)
        {
            int indiceSorteado = rand() % posicoesInimigosMedios.size();
            sf::Vector2f posEscolhida = posicoesInimigosMedios[indiceSorteado];

            Entidades::Personagens::Exercito *pExercito = new Entidades::Personagens::Exercito(posEscolhida.x, posEscolhida.y, 3, 15, 400);

            if (pExercito)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pExercito));
                vetorExercitos.push_back(pExercito);

                if (GC)
                {
                    GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo *>(pExercito));
                }
            }

            posicoesInimigosMedios.erase(posicoesInimigosMedios.begin() + indiceSorteado);
        }
    }

    void FasePrimeira::criarArbustos()
    {
        posicoesArbustos.clear();
        posicoesArbustos.push_back(sf::Vector2f(500.0f, 210.0f));
        posicoesArbustos.push_back(sf::Vector2f(1200.0f, 210.0f));
        posicoesArbustos.push_back(sf::Vector2f(300.0f, 580.0f));
        posicoesArbustos.push_back(sf::Vector2f(900.0f, 580.0f));
        posicoesArbustos.push_back(sf::Vector2f(400.0f, 960.0f));
        posicoesArbustos.push_back(sf::Vector2f(1300.0f, 960.0f));

        int quantidade = (rand() % 4) + 3;

        sf::Vector2f tamanhoPadrao(100.0f, 40.0f);

        for (int i = 0; i < quantidade; i++)
        {
            int indiceSorteado = rand() % posicoesArbustos.size();
            sf::Vector2f posEscolhida = posicoesArbustos[indiceSorteado];

            Entidades::Obstaculos::Arbusto *pArbusto = new Entidades::Obstaculos::Arbusto(posEscolhida.x, posEscolhida.y, tamanhoPadrao.x, tamanhoPadrao.y);

            if (pArbusto)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pArbusto));
                if (GC)
                {
                    GC->incluirObstaculo(pArbusto);
                }
            }

            posicoesArbustos.erase(posicoesArbustos.begin() + indiceSorteado);
        }
    }

    void FasePrimeira::criarInimigos()
    {
        criarInimFaceis();
        criarInimMedios();
    }

    void FasePrimeira::criarObstaculo()
    {
        criarPlataformas();
        criarArbustos();
        criarPortal(1750.0f, 110.0f);
    }

    void FasePrimeira::criarProjeteis()
    {
        for (int i = 0; i < 50; i++)
        {
            Entidades::Projetil *novoProjetil = new Entidades::Projetil(-500.0f, -500.0f, false, 1);
            incluirProjetil(novoProjetil);
        }
    }

}