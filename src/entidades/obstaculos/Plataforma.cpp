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
                sf::Vector2f posJog = p->getPosicao();
                float pLarg = p->getpFig()->getSize().x;
                float pAlt = p->getpFig()->getSize().y;

                sf::Vector2f posPlat = this->getPosicao();
                float platLarg = this->getpFig()->getSize().x;
                bool alinhadoY = (posJog.y + pAlt) >= posPlat.y && (posJog.y + pAlt) <= posPlat.y + altura;

                bool alinhadoX = posJog.x + pLarg > posPlat.x && posJog.x < posPlat.x + platLarg;

                if (alinhadoX && alinhadoY)
                {
                    p->setPosicao(sf::Vector2f(posJog.x, posPlat.y - pAlt));
                    sf::Vector2f velJog = p->getVelocidade();
                    velJog.y = 0.0f;
                    p->setVelocidade(velJog);
                    p->setNoChao(true);
                }
            }
        }

        void Plataforma::executar()
        {
        }
    }
}