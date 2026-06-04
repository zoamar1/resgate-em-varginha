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

    pJog1 = new Entidades::Personagens::Jogador(100.0f, ALTURA - 100, 100, 0);
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
            Fases::Fase *faseDeletada = nullptr;
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
                    pFase1->incluirJogador(pJog1, sf::Vector2f(100.0f, ALTURA - 100));
                }
                
                pFase1->executar();
                if (pJog1->get_vida_atual() <= 0)
                {
                    estado = MENU;
                    faseDeletada = pFase1;
                    pFase1 = NULL;
                    pJog1->set_vida_atual(pJog1->get_num_vidas());
                }
                break;
            }
            case FASE2:
            {
                break;
            }
            }
            pGG->desenhaJanela();

            if (faseDeletada)
            {
                delete faseDeletada;
                faseDeletada = NULL;
            }
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

Ente* Jogo::getCenarioAtual()
{
    if(estado == MENU)
    {
        return pMenu;
    }
    if(estado == FASE1)
    {
        return pFase1;
    }
}