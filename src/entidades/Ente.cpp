#include "entidades/Ente.hpp"
using namespace Gerenciadores;  

// FALTA IMPLEMENTAR FUNCOES

Gerenciador_Grafico *Ente::pGG = NULL;

Ente::Ente() : id(-1), pFig(NULL)
{

}

Ente::~Ente()
{
    if (pFig)
    {
        delete pFig; 
        pFig = NULL;
    }
    id = -1;
}

void Ente::desenhar()
{
    pGG->desenhaEnte(this);
}


void Ente::setGG(Gerenciadores::Gerenciador_Grafico *pG)
{
    pGG = pG;
}
