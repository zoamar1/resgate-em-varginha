#include "fases/FasePrimeira.hpp"
#include "entidades/obstaculos/Arbusto.hpp"

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
    }

    void FasePrimeira::criarInimMedios()
    {
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
        criarInimFaceis(sf::Vector2f(300.0f, 863.0f));
        criarInimFaceis(sf::Vector2f(800.0f, 863.0f));
        criarInimFaceis(sf::Vector2f(1200.0f, 323.0f));
        criarInimFaceis(sf::Vector2f(900.0f, 123.0f));
    }

    void FasePrimeira::criarObstaculo()
    {
        criarPlataformas();
        criarArbustos();
    }

}