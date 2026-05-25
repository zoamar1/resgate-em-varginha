#pragma once
#include "Header.hpp"
#include "Personagem.hpp"

namespace Entidades { namespace Obstaculos { class Plataforma; } }

namespace Personagens
{
    class Inimigo;

    class Jogador : public Personagem
    {
    protected:
        int pontos;
        const Entidades::Obstaculos::Plataforma* pPlataforma;
    public:
        Jogador(int posX = 0, int posY = 0, int n = 3, int p = 0);
        ~Jogador();

        void executar();
        void salvar();
        void mover();
        void definirPlataforma(const Entidades::Obstaculos::Plataforma* plataforma);
    };
}
