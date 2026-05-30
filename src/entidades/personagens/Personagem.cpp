#include "personagens/Personagem.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Personagem::Personagem(float posX, float posY, float tamanhoX, float tamanhoY, int n) : Entidade(posX, posY, tamanhoX, tamanhoY),
                                                                                        num_vidas(n), vel_max(0), velx(0), vely(0)
        {
        }

        void Personagem::setVelX(float x)
        {
            velx = x;
        }

        void Personagem::setVelY(float y)
        {
            vely = y;
        }

        void Personagem::setVel_Max(float max)
        {
            vel_max = max;
        }

        float Personagem::getVelX() const
        {
            return velx;
        }

        float Personagem::getVelY() const
        {
            return vely;
        }

        float Personagem::getVel_Max() const
        {
            return vel_max;
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
