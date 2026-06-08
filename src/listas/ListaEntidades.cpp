#include "listas/ListaEntidades.hpp"
#include "entidades/personagens/Jogador.hpp"
#include "entidades/personagens/Personagem.hpp"
#include "entidades/personagens/Inimigo.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"

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

    void ListaEntidades::limparExcetoJogador(Entidades::Personagens::Jogador *pJogador)
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

    void ListaEntidades::removerMortos(Gerenciadores::Gerenciador_Colisoes *GC)
    {
        Entidades::Entidade *aux = LE.getPrimeiro();
        while (aux != NULL)
        {
            Entidades::Entidade *proximo = LE.getProximo();

            Entidades::Personagens::Personagem *p = dynamic_cast<Entidades::Personagens::Personagem *>(aux);

            Entidades::Personagens::Jogador *jog = dynamic_cast<Entidades::Personagens::Jogador *>(aux);

            if (p && !jog && p->get_vida_atual() <= 0)
            {
                if (GC)
                {
                    GC->removerInimigo(static_cast<Entidades::Personagens::Inimigo *>(p));
                }
                LE.remover(aux);
                delete aux;
            }

            aux = proximo;
        }
    }
}