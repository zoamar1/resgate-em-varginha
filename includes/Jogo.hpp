#pragma once
#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "gerenciadores/Gerenciador_Eventos.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"
#include "entidades/personagens/Jogador.hpp"
#include "fases/FasePrimeira.hpp"
#include "Menu.hpp"

class Jogo
{
public:
    enum Estados 
        {
            MENU,
            FASE1,
            FASE2
        };
private:
    Gerenciadores::Gerenciador_Grafico *pGG;
    Gerenciadores::Gerenciador_Eventos *pGE;
    Gerenciadores::Gerenciador_Colisoes *pGC;
    Estados estado;
    Menu menu;
    Entidades::Personagens::Jogador *pJog1;
public:
    Jogo();
    ~Jogo();
    void executar();
    Estados getEstado();
    void setEstado(Estados valor);
};