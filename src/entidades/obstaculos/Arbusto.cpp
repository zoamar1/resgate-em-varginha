#include "entidades/obstaculos/Arbusto.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Arbusto::Arbusto(int posX, int posY, int tamanhoX, int tamanhoY) : Obstaculo(posX, posY, tamanhoX, tamanhoY), largura(tamanhoX)
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
                p->setVelX(p->getVelX() * 0.5f);
            }
        }

        void Arbusto::executar(Entidades::Personagens::Jogador *p)
        {
            obstaculizar(p);
            desenhar();
        }
    }
}