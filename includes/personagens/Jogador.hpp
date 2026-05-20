#pragma once
#include "Header.hpp"
#include "Personagem.hpp"

namespace Personagens
{
    class Inimigo;

    class Jogador : public Personagem
    {
    protected:
        int pontos;

    public:
        // lembrar de mudar n(numero de vidas) para o padrao do jogador!!!!
        Jogador(int posX = 0, int posY = 0, int n = 3, int p = 0);
        ~Jogador();

        void colidir(Inimigo *pI);
        void executar();
        void salvar();
    };
}
