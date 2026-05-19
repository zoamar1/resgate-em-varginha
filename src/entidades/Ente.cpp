#include "entidades/Ente.hpp"
using namespace Gerenciadores;  

// FALTA IMPLEMENTAR FUNCOES

Gerenciador_Grafico *Ente::pGG = NULL;

Ente::Ente() : id(-1), pFig(NULL)
{

}

Ente::~Ente()
{
    id = -1;
}

void Ente::setGG(Gerenciadores::Gerenciador_Grafico *pG)
{
    pGG = pG;
}
