#pragma once
#include "Header.hpp"
#include "entidades/Entidade.hpp"

class Projetil : public Entidade
{
protected:
    bool ativo;

public:
    Projetil(int posX, int posY, bool flag);
    ~Projetil();

    void executar();
    void salvar();
};