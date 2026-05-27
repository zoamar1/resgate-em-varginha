#pragma once
#include "Header.hpp"
#include "entidades/Ente.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "listas/ListaEntidades.hpp"

namespace Fases {

    class Fase : public Ente {

    protected:
        Listas::ListaEntidades lista_ents;
        Gerenciadores::Gerenciador_Colisoes* GC;
    public:
        Fase(Gerenciadores::Gerenciador_Colisoes* pGC);
        virtual ~Fase();
        virtual void executar();
    protected:
        void criarInimFaceis();
        void criarPlataformas();
        void criarCenario();
        virtual void criarInimigos() = 0; 
        virtual void criarObstaculo() = 0;
    };

}