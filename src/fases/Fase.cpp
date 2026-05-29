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
    void Fase::criarChao()
    {
        Entidades::Chao *chao = new Entidades::Chao();
        chao->executar();
    }
    void Fase::executar()
    {
        criarChao();
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