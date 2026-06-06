#include "fases/FasePrimeira.hpp"
#include "entidades/obstaculos/Arbusto.hpp"
#include "entidades/personagens/Exercito.hpp"

namespace Fases
{

    FasePrimeira::FasePrimeira(Gerenciadores::Gerenciador_Colisoes *pGC) : Fase(pGC), maxInimMedios(50)
    {
        pFig->setSize({LARGURA - 1, ALTURA - 1});
        pFig->setOrigin({0, 0});
        aplicarTextura(Gerenciadores::FundoFase1);
        criarCenario();
    }

    FasePrimeira::~FasePrimeira()
    {
        posicoesPlataformas.clear();
        posicoesInimigosMedios.clear();
    }

    void FasePrimeira::criarInimMedios()
    {
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

            Entidades::Personagens::Exercito *pExercito = new Entidades::Personagens::Exercito(posEscolhida.x, posEscolhida.y, 3, 15, 10);

            if (pExercito)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pExercito));

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
        posicoesArbustos.push_back(sf::Vector2f(500.0f, 210.0f));
        posicoesArbustos.push_back(sf::Vector2f(1200.0f, 210.0f));
        posicoesArbustos.push_back(sf::Vector2f(300.0f, 580.0f));
        posicoesArbustos.push_back(sf::Vector2f(900.0f, 580.0f));
        posicoesArbustos.push_back(sf::Vector2f(400.0f, 950.0f));
        posicoesArbustos.push_back(sf::Vector2f(1300.0f, 950.0f));

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
    }

    void FasePrimeira::criarProjeteis()
    {

        for (int i = 0; i < 1000; i++)
        {
            Entidades::Projetil *novoProjetil = new Entidades::Projetil(-500.0f, -500.0f, false, 30);
            incluirProjetil(novoProjetil);
        }
    }

}