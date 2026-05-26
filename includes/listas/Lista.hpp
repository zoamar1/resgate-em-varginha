#pragma once
#include "Header.hpp"

namespace Listas{
    template<class TL>
    class Lista
    {
    private:
        template<class TE>
        class Elemento
        {
            private:
                Elemento<TE>* pProx;
                TE* pInfo;
            public:
                Elemento();
                ~Elemento();
                void incluir(TE* p);
                void setProx(Elemento<TE>* pE);
                Elemento getPRoximo()
        }

        Elemento<TL>* pPrimeiro;
        Elemento<TL>* pUltimo;
    public:
        Lista();
        ~Lista();
        void incluir(T* p);
        void limpar();
    
    };
}