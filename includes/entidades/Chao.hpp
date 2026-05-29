#pragma once
#include "entidades/Entidade.hpp"
#include "Header.hpp"

namespace Entidades
{
    class Chao : public Entidade
    {
    private:
        
    public:
        Chao();
        ~Chao();
        void executar();
        void salvar();
    };    
}