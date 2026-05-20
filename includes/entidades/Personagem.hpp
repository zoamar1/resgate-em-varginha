#pragma once
#include "Header.hpp"
#include "Entidade.hpp"

class Personagem : public Entidade
{
protected:
    int num_vidas;

public:
    Personagem(int posX = 0, int posY = 0, int n = 0);
    ~Personagem();

    // void salvarDataBuffer();
    virtual void executar() = 0;
    virtual void salvar() = 0;
    virtual void mover() = 0;
};