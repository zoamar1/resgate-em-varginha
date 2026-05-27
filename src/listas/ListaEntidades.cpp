#include "listas/ListaEntidades.hpp"

namespace Listas
{
    ListaEntidades::ListaEntidades() : LE()
    {
    }
    ListaEntidades::~ListaEntidades()
    {
        LE.limpar();
    }
    void ListaEntidades::incluir(Entidades::Entidade *pE)
    {
        LE.incluir(pE);
    }
    void ListaEntidades::percorrer()
    {
        Entidades::Entidade* aux = LE.getPrimeiro();
        while (aux != NULL)
        {
            aux->executar();
            aux = LE.getProximo();
        }
    }

}