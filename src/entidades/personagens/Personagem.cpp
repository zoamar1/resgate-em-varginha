#include "personagens/Personagem.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Personagem::Personagem(float posX, float posY, float tamanhoX, float tamanhoY, int n) : Entidade(posX, posY, tamanhoX, tamanhoY, true),
                                                                                        num_vidas(n)
        {
        }

        Personagem::~Personagem()
        {
        }

        void Personagem::recebeDano(int dano)
        {
            num_vidas -= dano;
        }
    }
}
