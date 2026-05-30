#include "entidades/obstaculos/Plataforma.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Plataforma::Plataforma(float posX, float posY, float tamanhoX, float tamanhoY) : Obstaculo(posX, posY, tamanhoX, tamanhoY), altura(tamanhoY)
        {
        }

        Plataforma::~Plataforma()
        {
        }

        void Plataforma::salvar()
        {
        }

        void Plataforma::obstaculizar(Entidades::Personagens::Jogador *p)
        {
            if (p && p->getpFig())
            {
                float pX = p->getX();
                float pY = p->getY();
                float pLarg = p->getpFig()->getSize().x;
                float pAlt = p->getpFig()->getSize().y;

                float platX = this->getX();
                float platY = this->getY();
                float platLarg = this->getpFig()->getSize().x;
                bool alinhadoY = (pY + pAlt) >= platY && (pY + pAlt) <= platY + altura;

                bool alinhadoX = pX + pLarg > platX && pX < platX + platLarg;

                if (alinhadoX && alinhadoY)
                {
                    p->setY(platY - pAlt);
                    p->setVelY(0.0f);
                }
            }
        }

        void Plataforma::executar(Entidades::Personagens::Jogador *p)
        {
            obstaculizar(p);
            desenhar();
        }
    }
}