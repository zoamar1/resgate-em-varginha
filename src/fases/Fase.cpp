#include "fases/Fase.hpp"

namespace Fases
{
    Fase::Fase(Gerenciadores::Gerenciador_Colisoes *pGC) : lista_ents(), GC(pGC), pChao(NULL)
    {
    }
    Fase::~Fase()
    {
        GC = NULL;
        pChao = NULL;
    }
    void Fase::criarChao()
    {
        if (!pChao)
        {
            pChao = new Entidades::Chao();
            lista_ents.incluir(pChao);
        }
    }
    void Fase::executar()
    {
        criarChao();
        lista_ents.percorrer();

        if (GC)
        {
            GC->executar();

            if (pChao && GC->getJogador1())
            {
                GC->colisaoPersonagemChao(GC->getJogador1(), pChao);
            }
        }
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