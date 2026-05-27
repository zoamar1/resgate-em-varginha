#pragma once
#include "fases/Fase.hpp"

namespace Fases {
    class FasePrimeira : public Fase {
    private:
        const int maxInimMedios;

    public:
        FasePrimeira(Gerenciadores::Gerenciador_Colisoes* pGC);
        ~FasePrimeira();

    protected:
        void criarInimMedios();
        void criarObstMedios();

        void criarInimgos(); 
        void criarObstaculo();
    };
}