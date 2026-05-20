#include "Jogador.hpp"

namespace Personagens
{
    Jogador::Jogador(int posX, int posY, int n, int p) : Personagem(posX, posY, n), pontos(p)
    {
    }

    Jogador::~Jogador()
    {
    }
}