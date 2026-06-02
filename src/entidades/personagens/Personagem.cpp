#include "personagens/Personagem.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Personagem::Personagem(float posX, float posY, float tamanhoX, float tamanhoY, int n) : Entidade(sf::Vector2f(posX, posY), sf::Vector2f(tamanhoX, tamanhoY), true),
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

        void Personagem::operator++()
        {
            // fazer a verificação com o limite de vidaas
            num_vidas++;
        }
    }
}
