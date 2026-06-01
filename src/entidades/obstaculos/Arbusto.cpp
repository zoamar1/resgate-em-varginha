#include "entidades/obstaculos/Arbusto.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Arbusto::Arbusto(float posX, float posY, float tamanhoX, float tamanhoY) : Obstaculo(posX, posY, tamanhoX, tamanhoY), largura(tamanhoX)
        {
            if (pFig)
            {
                aplicarTextura(Gerenciadores::Arbusto);
            }
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
                sf::Vector2f pos = p->getPosicao();
                sf::Vector2f vel = p->getVelocidade();
                
                pos.x -= vel.x * 0.5f;
                pos.y -= vel.y * 0.5F;
                p->setPosicao(pos);
            }
        }

        void Arbusto::executar()
        {
            
        }
    }
}