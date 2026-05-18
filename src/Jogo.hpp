#pragma once
#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "gerenciadores/Gerenciador_Eventos.hpp"

class Jogo
{
private:
    Gerenciadores::Gerenciador_Grafico *pGG;
    Gerenciadores::Gerenciador_Eventos *pGE;

public:
    Jogo();
    ~Jogo();
    void executar();
};