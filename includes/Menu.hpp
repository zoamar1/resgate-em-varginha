#pragma once
#include "Header.hpp"
#include "entidades/Ente.hpp"

class Jogo;

class Menu : public Ente
{
    private:
        Jogo* pJogo;
    public:
        Menu();
        ~Menu();
        void executar();
};