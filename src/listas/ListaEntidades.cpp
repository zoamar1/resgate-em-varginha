#include "listas/ListaEntidades.hpp"
#include "entidades/personagens/Jogador.hpp"

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
        Entidades::Entidade *aux = LE.getPrimeiro();
        while (aux != NULL)
        {
            aux->executar();
            aux = LE.getProximo();
        }
    }

    void ListaEntidades::desenhar()
    {
        Entidades::Entidade *aux = LE.getPrimeiro();
        while (aux != NULL)
        {
            aux->desenhar();
            aux = LE.getProximo();
        }
    }

    void ListaEntidades::limparExcetoJogador(Entidades::Personagens::Jogador* pJogador)
    {
        Entidades::Entidade *aux = LE.getPrimeiro();
        while (aux != NULL)
        {
            if (aux != pJogador)
            {
                delete aux;
            }
            aux = LE.getProximo();
        }

        LE.limpar();
    }
}