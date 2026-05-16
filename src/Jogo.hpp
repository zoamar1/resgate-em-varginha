#pragma once
#include "Gerenciador_Grafico.hpp"
#include "Gerenciador_Eventos.hpp"

class Jogo
{
    private:
        Gerenciadores::Gerenciador_Grafico* pGG;
        Gerenciadores::Gerenciador_Eventos* pGE;
    public:
        Jogo();
        ~Jogo();
        void executar();
};