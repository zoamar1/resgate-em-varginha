#include "fases/FasePrimeira.hpp"

namespace Fases
{

    FasePrimeira::FasePrimeira(Gerenciadores::Gerenciador_Colisoes *pGC) : Fase(pGC), maxInimMedios(50)
    {
        criarCenario();
    }
    FasePrimeira::~FasePrimeira()
    {
    }

    void FasePrimeira::criarInimMedios()
    {
    }
    void FasePrimeira::criarObstMedios()
    {
    }

    void FasePrimeira::criarInimigos()
    {
        std::cout << "teste" << std::endl;
    }
    void FasePrimeira::criarObstaculo()
    {
        criarPlataformas(sf::Vector2f(550.0f, 100.0f), sf::Vector2f(200.0f, 30.0f));

        criarPlataformas(sf::Vector2f(1300.0f, 100.0f), sf::Vector2f(200.0f, 30.0f));

        criarPlataformas(sf::Vector2f(250.0f, 250.0f), sf::Vector2f(1400.0f, 30.0f));

        criarPlataformas(sf::Vector2f(200.0f, 380.0f), sf::Vector2f(120.0f, 30.0f));
        criarPlataformas(sf::Vector2f(50.0f, 50.0f), sf::Vector2f(120.0f, 30.0f));

        criarPlataformas(sf::Vector2f(350.0f, 450.0f), sf::Vector2f(350.0f, 30.0f));

        criarPlataformas(sf::Vector2f(1100.0f, 450.0f), sf::Vector2f(300.0f, 30.0f));

        criarPlataformas(sf::Vector2f(0.0f, 650.0f), sf::Vector2f(1600.0f, 30.0f));

        criarPlataformas(sf::Vector2f(400.0f, 850.0f), sf::Vector2f(250.0f, 30.0f));

        criarPlataformas(sf::Vector2f(1100.0f, 850.0f), sf::Vector2f(250.0f, 30.0f));

        criarPlataformas(sf::Vector2f(1650.0f, 900.0f), sf::Vector2f(120.0f, 30.0f));

        criarPlataformas(sf::Vector2f(1750.0f, 750.0f), sf::Vector2f(120.0f, 30.0f));
    }

}