#include "Jogo.hpp"

Jogo::Jogo() : pGG(Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()),
               pGE(Gerenciadores::Gerenciador_Eventos::getGerenciador_Eventos(this)),
               pGC(Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes()),
               estado(MENU),
               pMenu(NULL),
               pJog1(NULL),
               pFase1(NULL)
{
    Ente::setGG(pGG);
    pGE->setGerenciador_Grafico(pGG);

    pMenu = new Menu();

    pJog1 = new Entidades::Personagens::Jogador(300.0f, 300.0f, 100, 0);
    pGE->setJogador1(pJog1);
    pGC->setJogador1(pJog1);
};

Jogo::~Jogo()
{
    if (pJog1)
    {
        delete pJog1;
        pJog1 = NULL;
    }

    if (pFase1)
    {
        delete pFase1;
        pFase1 = NULL;
    }

    pGG = NULL;
};

void Jogo::executar()
{
    if (pGG && pGE)
    {
        while (pGG->janelaAberta())
        {
            pGE->executar();
            pGG->limpaJanela();
            switch (getEstado())
            {
            case MENU:
            {
                pMenu->executar();
                break;
            }
            case FASE1:
            {
                if (!pFase1)
                {
                    pFase1 = new Fases::FasePrimeira(pGC);
                    pFase1->incluirJogador(pJog1);
                }
                
                pFase1->executar();
                break;
            }
            case FASE2:
            {
                break;
            }
            }
            pGG->desenhaJanela();
        }
    }
};

Jogo::Estados Jogo::getEstado()
{
    return estado;
}

void Jogo::setEstado(Estados valor)
{
    estado = valor;
}
