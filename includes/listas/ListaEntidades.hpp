#pragma once
#include "listas/Lista.hpp"
#include "entidades/Entidade.hpp"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;
    }
}

namespace Gerenciadores
{
    class Gerenciador_Colisoes;
}

namespace Listas
{
    class ListaEntidades
    {
    private:
        Lista<Entidades::Entidade> LE;

    public:
        ListaEntidades();
        ~ListaEntidades();
        void incluir(Entidades::Entidade *pE);
        void percorrer();
        void desenhar();
        void limparExcetoJogadores();
        void removerMortos(Gerenciadores::Gerenciador_Colisoes *GC);
    };
}