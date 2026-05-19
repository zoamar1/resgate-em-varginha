#pragma once
#include "Header.hpp"
#include "Ente.hpp"
// using namespace std;

class Entidade : public Ente
{
protected:
    int x;
    int y;

    // ostream buffer;

public:
    Entidade(int posX, int posY);
    virtual ~Entidade();

    virtual void executar() = 0;
    virtual void salvar() = 0;

//protected:
    //void salvarDataBuffer();
};