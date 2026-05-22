#include "Jogo.hpp"

Jogo::Jogo() : 
    pGG(Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()), 
    pGE(Gerenciadores::Gerenciador_Eventos::getGerenciador_Eventos()), 
    estado(MENU),
    menu()
{
    pGE->setGerenciador_Grafico(pGG);
    Ente::setGG(pGG);
};

Jogo::~Jogo()
{
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
                }
                case FASE1:
                {
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

int Jogo::getEstado()
{
    return static_cast<int>(estado);
}
void Jogo::setEstado(const int valor)
{
    estado = static_cast<Estados>(valor);
}