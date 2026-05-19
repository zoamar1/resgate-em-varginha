#pragma once
#include "Header.hpp"
#include "gerenciadores/Gerenciador_Grafico.hpp"

class Ente
{
protected:
    int id;
    static Gerenciadores::Gerenciador_Grafico *pGG;
    sf::RectangleShape* pFig;

public:
    Ente();
    virtual ~Ente();
    virtual void executar() = 0;
    void desenhar();
    static void setGG(Gerenciadores::Gerenciador_Grafico *pG);
    sf::RectangleShape* getpFig();
};