#pragma once
#include "gerenciadores/Gerenciador_Grafico.hpp"
#include "gerenciadores/Gerenciador_Eventos.hpp"
#include "personagens/Jogador.hpp"
#include "entidades/Plataforma.hpp"
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
    Estados estado;
    Menu menu;
    Plataforma plataforma;
    Personagens::Jogador *pJog1;
public:
    Jogo();
    ~Jogo();
    void executar();
    Estados getEstado();
    void setEstado(Estados valor);
};