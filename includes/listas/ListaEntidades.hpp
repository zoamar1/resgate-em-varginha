#pragma once
#include "listas/Lista.hpp"
#include "entidades/Entidade.hpp"

namespace Listas {
    class ListaEntidades
    {
        private:
            Lista<Entidades::Entidade> LE;
        public:
            ListaEntidades();
            ~ListaEntidades();
            void incluir(Entidades::Entidade* pE);
            void percorrer();
    };
}