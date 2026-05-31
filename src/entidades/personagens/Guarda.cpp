#include "personagens/Guarda.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        Guarda::Guarda(float posX, float posY, int n, int maldade, int f) : Inimigo(posX, posY, n, maldade), forca(f)
        {
            setVel_Max(0.0f);

            if (pFig)
            {
                pFig->setSize(sf::Vector2f(70.0f, 127.0f));
                pFig->setPosition(sf::Vector2f(posX, posY));
            }

            aplicarTextura(Gerenciadores::Guarda);
        }

        Guarda::~Guarda() {}

        void Guarda::danificar(Jogador *p)
        {
            if (p)
            {
                p->recebeDano(nivel_maldade);
            }
        }

        void Guarda::mover()
        {
        }

        void Guarda::salva()
        {
        }

        void Guarda::executar()
        {
        }
    }
}