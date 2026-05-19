#pragma once
#include "Header.hpp"
#include "Jogo.hpp"
#include "entidades/Ente.hpp"

class Menu : public Ente
{
    private:
        Jogo* pJogo;
    public:
        Menu();
        ~Menu();
        void executar();
};