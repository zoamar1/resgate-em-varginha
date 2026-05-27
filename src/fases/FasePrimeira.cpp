#include "fases/FasePrimeira.hpp"

namespace Fases
{

    FasePrimeira::FasePrimeira(Gerenciadores::Gerenciador_Colisoes *pGC) : Fase(pGC), maxInimMedios(50)
    {
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
    }

}