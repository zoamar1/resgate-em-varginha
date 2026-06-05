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
    }

    void FasePrimeira::criarInimMedios()
    {
    }
    void FasePrimeira::criarArbustos()
    {
        Entidades::Obstaculos::Arbusto *pArbusto = new Entidades::Obstaculos::Arbusto(400.0f, 950.0f, 100.0f, 40.0f);

        if (pArbusto)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade *>(pArbusto));
            if (GC)
            {
                GC->incluirObstaculo(pArbusto);
            }
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
       /* criarPlataformas(sf::Vector2f(550.0f, 100.0f), sf::Vector2f(200.0f, 30.0f));
        criarPlataformas(sf::Vector2f(1300.0f, 100.0f), sf::Vector2f(200.0f, 30.0f));

        criarPlataformas(sf::Vector2f(50.0f, 200.0f), sf::Vector2f(120.0f, 30.0f));
        criarPlataformas(sf::Vector2f(150.0f, 380.0f), sf::Vector2f(120.0f, 30.0f));
        criarPlataformas(sf::Vector2f(350.0f, 485.0f), sf::Vector2f(350.0f, 30.0f));
        criarPlataformas(sf::Vector2f(1100.0f, 450.0f), sf::Vector2f(300.0f, 30.0f));

        criarPlataformas(sf::Vector2f(400.0f, 850.0f), sf::Vector2f(250.0f, 30.0f));
        criarPlataformas(sf::Vector2f(1100.0f, 850.0f), sf::Vector2f(250.0f, 30.0f));
        criarPlataformas(sf::Vector2f(1650.0f, 900.0f), sf::Vector2f(120.0f, 30.0f));
        criarPlataformas(sf::Vector2f(1750.0f, 750.0f), sf::Vector2f(120.0f, 30.0f));*/ 

        criarArbustos();
    }

}