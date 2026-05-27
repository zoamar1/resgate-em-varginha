#pragma once

namespace Listas {

    template<class TL>
    class Lista {
    private:
        template<class TE>
        class Elemento {
        private:
            Elemento<TE>* pProx;
            TE* pInfo;

        public:
            Elemento() {
                pProx = NULL; 
                pInfo = NULL;
            }
            
            ~Elemento() {
            }
            
            void incluir(TE* p) {
                pInfo = p;
                setProx(NULL);
            }
            
            void setProx(Elemento<TE>* pE) {
                pProx = pE;
            }
            
            Elemento<TE>* getProximo() const { 
                return pProx;
            }
        };

        Elemento<TL>* pPrimeiro;
        Elemento<TL>* pUltimo;

    public:
        Lista() {
            pPrimeiro = NULL;
            pUltimo = NULL;
        }
        
        ~Lista() {
            limpar();
        }
        
        void incluir(TL* p) {
            if (!p) return;
            
            if (!pPrimeiro) {
                pPrimeiro = new Elemento<TL>();
                pPrimeiro->incluir(p);
                pUltimo = pPrimeiro;
            } else {
                Elemento<TL>* aux = new Elemento<TL>(); 
                aux->incluir(p);
                pUltimo->setProx(aux);
                pUltimo = aux;
            }
        }
        
        void limpar() {
            Elemento<TL>* aux = pPrimeiro; 
            
            while(aux) {
                Elemento<TL>* prox = aux->getProximo();
                delete aux;
                aux = prox;
            }
            
            pPrimeiro = NULL;
            pUltimo = NULL;
        }
    };

}