#include "entidades/obstaculos/Plataforma.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Plataforma::Plataforma(float posX, float posY, float tamanhoX, float tamanhoY) : Obstaculo(posX, posY, tamanhoX, tamanhoY), altura(tamanhoY)
        {
            aplicarTextura(Gerenciadores::Plataforma);
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
                sf::Vector2f tamJog = p->getpFig()->getSize();

                sf::Vector2f posPlat = this->getPosicao();
                sf::Vector2f tamPlat = this->getpFig()->getSize();

                sf::Vector2f centroJog = posJog + (tamJog / 2.0f);
                sf::Vector2f centroPlat = posPlat + (tamPlat / 2.0f);

                float distX = std::abs(centroJog.x - centroPlat.x);//std::abs -> tira módulo
                float distY = std::abs(centroJog.y - centroPlat.y);

                float somaMetadeLargura = (tamJog.x + tamPlat.x) / 2.0f;
                float somaMetadeAltura = (tamJog.y + tamPlat.y) / 2.0f;

                float interX = somaMetadeLargura - distX;
                float interY = somaMetadeAltura - distY;

                if (interX > 0.0f && interY > 0.0f) 
                {
                    
                    if (interX > interY)
                    {
                        if (centroJog.y < centroPlat.y)
                        {
                            p->setPosicao(sf::Vector2f(posJog.x, posPlat.y - tamJog.y));
                            p->setVelY(0.0f);
                            p->setNoChao(true);
                        }
                        else
                        {
                            p->setPosicao(sf::Vector2f(posJog.x, posPlat.y + tamPlat.y));
                            p->setVelY(0.0f); 
                        }
                    }
                    else
                    {
                        if (centroJog.x < centroPlat.x)
                        {
                            
                            p->setPosicao(sf::Vector2f(posPlat.x - tamJog.x, posJog.y));
                            p->setVelX(0.0f);
                        }
                        else
                        {
                            p->setPosicao(sf::Vector2f(posPlat.x + tamPlat.x, posJog.y));
                            p->setVelX(0.0f);
                        }
                    }
                }
            }
        }

        void Plataforma::executar()
        {
        }
    }
}