#include "fases/FaseSegunda.hpp"

namespace Fases
{

    FaseSegunda::FaseSegunda(Gerenciadores::Gerenciador_Colisoes *pGC) : Fase(pGC), maxETs(50)
    {
        pFig->setSize({LARGURA - 1, ALTURA - 1});
        pFig->setOrigin({0, 0});
        aplicarTextura(Gerenciadores::FundoFase1);
        criarCenario();
    }

    FaseSegunda::~FaseSegunda()
    {
        posicoesEspinhos.clear();
    }

    void FaseSegunda::criarEspinhos()
    {
    }

    void FaseSegunda::criarObstaculo()
    {
        criarPlataformas();
    }

    void FaseSegunda::criarInimigos()
    {
        criarInimFaceis();
    }

    void FaseSegunda::criarProjeteis()
    {
        for (int i = 0; i < 1000; i++)
        {
            Entidades::Projetil *novoProjetil = new Entidades::Projetil(-500.0f, -500.0f, false, 1);
            incluirProjetil(novoProjetil);
        }
    }

    void FaseSegunda::executar()
    {
        Fase::executar();
    }

}