#include "Jogo.hpp"

Jogo::Jogo() : 
    pGG(Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()), 
    pGE(Gerenciadores::Gerenciador_Eventos::getGerenciador_Eventos(this)), 
    estado(MENU),
    menu(),
    pJog1(NULL)
{
    pGE->setGerenciador_Grafico(pGG);
    Ente::setGG(pGG);
};

Jogo::~Jogo()
{
    if (pJog1)
    {
        delete pJog1;
        pJog1 = NULL;
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
            switch(getEstado())
            {
                case MENU:
                {
                    menu.executar();
                    break;
                }
                case FASE1:
                {
                    if (!pJog1) pJog1 = new Entidades::Personagens::Jogador(300, 300);
                    pGE->setJogador1(pJog1);
                    pJog1->executar();

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