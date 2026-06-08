#pragma once
#include "Header.hpp"
namespace Listas
{

    template <class TL>
    class Lista
    {
    private:
        template <class TE>
        class Elemento
        {
        private:
            Elemento<TE> *pProx;
            TE *pInfo;

        public:
            Elemento()
            {
                pProx = NULL;
                pInfo = NULL;
            }

            ~Elemento()
            {
            }

            void incluir(TE *p)
            {
                pInfo = p;
                setProx(NULL);
            }

            void setProx(Elemento<TE> *pE)
            {
                pProx = pE;
            }

            Elemento<TE> *getProximo() const
            {
                return pProx;
            }

            TE *getInfo() const
            {
                return pInfo;
            }
        };

        Elemento<TL> *pPrimeiro;
        Elemento<TL> *pUltimo;
        Elemento<TL> *pAtual;

    public:
        Lista()
        {
            pPrimeiro = NULL;
            pUltimo = NULL;
            pAtual = NULL;
        }

        ~Lista()
        {
            limpar();
        }

        void incluir(TL *p)
        {
            if (!p)
                return;

            if (!pPrimeiro)
            {
                pPrimeiro = new Elemento<TL>();
                pPrimeiro->incluir(p);
                pUltimo = pPrimeiro;
            }
            else
            {
                Elemento<TL> *aux = new Elemento<TL>();
                aux->incluir(p);
                pUltimo->setProx(aux);
                pUltimo = aux;
            }
        }

        void limpar()
        {
            Elemento<TL> *aux = pPrimeiro;

            while (aux)
            {
                Elemento<TL> *prox = aux->getProximo();
                delete aux;
                aux = prox;
            }

            pPrimeiro = NULL;
            pUltimo = NULL;
        }

        void remover(TL *p)
        {
            if (!p || !pPrimeiro)
                return;

            if (pPrimeiro->getInfo() == p)
            {
                Elemento<TL> *aux = pPrimeiro;
                pPrimeiro = pPrimeiro->getProximo();
                if (!pPrimeiro)
                    pUltimo = NULL;
                delete aux;
                return;
            }

            Elemento<TL> *anterior = pPrimeiro;
            Elemento<TL> *atual = pPrimeiro->getProximo();
            while (atual)
            {
                if (atual->getInfo() == p)
                {
                    anterior->setProx(atual->getProximo());
                    if (atual == pUltimo)
                        pUltimo = anterior;
                    delete atual;
                    return;
                }
                anterior = atual;
                atual = atual->getProximo();
            }
        }

        TL *getPrimeiro()
        {
            pAtual = pPrimeiro;
            if (pAtual)
            {
                return pAtual->getInfo();
            }
            return NULL;
        }

        TL *getProximo()
        {
            if (pAtual)
            {
                pAtual = pAtual->getProximo();
            }

            if (pAtual)
            {
                return pAtual->getInfo();
            }
            return NULL;
        }
    };

}