#include "fases/Fase.hpp"

namespace Fases
{
    Fase::Fase(Gerenciadores::Gerenciador_Colisoes* pGC) : lista_ents(), GC(pGC)
    {

    }
    Fase::~Fase()
    {
        GC = NULL;
    }
    void Fase::executar()
    {
        lista_ents.percorrer();
    }
    void Fase::criarInimFaceis()
    {

    }
    void Fase::criarPlataformas()
    {

    }
    void Fase::criarCenario()
    {

    }
    
}