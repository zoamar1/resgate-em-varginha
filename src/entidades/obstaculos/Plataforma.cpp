#include "entidades/obstaculos/Plataforma.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Plataforma::Plataforma(int posX, int posY, int tamanhoX, int tamanhoY) : Obstaculo(posX, posY, tamanhoX, tamanhoY), altura(tamanhoY)
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
                float pLarg = static_cast<float>(p->getpFig()->getSize().x);
                float pAlt = static_cast<float>(p->getpFig()->getSize().y);

                float platX = this->getX();
                float platY = this->getY();
                float platLarg = static_cast<float>(this->getpFig()->getSize().x);
                float platAlt = static_cast<float>(this->getpFig()->getSize().y);

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