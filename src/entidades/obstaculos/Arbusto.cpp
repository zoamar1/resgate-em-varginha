#include "entidades/obstaculos/Arbusto.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Arbusto::Arbusto(float posX, float posY, float tamanhoX, float tamanhoY) : Obstaculo(posX, posY, tamanhoX, tamanhoY), largura(tamanhoX)
        {
        }

        Arbusto::~Arbusto()
        {
        }

        void Arbusto::salvar()
        {
        }

        void Arbusto::obstaculizar(Entidades::Personagens::Jogador *p)
        {
            if (p)
            {
                sf::Vector2f vel = p->getVelocidade();
                vel.x *= 0.5f;
                p->setVelocidade(vel);
            }
        }

        void Arbusto::executar(Entidades::Personagens::Jogador *p)
        {
            obstaculizar(p);
        }
    }
}