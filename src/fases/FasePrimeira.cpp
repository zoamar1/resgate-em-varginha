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
        criarPlataformas(sf::Vector2f(100.0f, 860.0f), sf::Vector2f(200.0f, 20.0f));
        criarPlataformas(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(150.0f, 20.0f));
        criarPlataformas(sf::Vector2f(650.0f, 300.0f), sf::Vector2f(200.0f, 20.0f));
    }

}