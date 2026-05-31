#include "personagens/ET_Varginha.hpp"
#include "personagens/Jogador.hpp"

namespace Entidades
{
    namespace Personagens
    {
        ET_Varginha::ET_Varginha(float posX, float posY, int n, int maldade, int ml) : Inimigo(posX, posY, n, maldade), multiplicador_laser(ml)
        {
        }

        ET_Varginha::~ET_Varginha() {}

        void ET_Varginha::danificar(Jogador *p)
        {
            if (p)
            {
                // falta concluir essa parte
            }
        }

        void ET_Varginha::executar()
        {
        }
    }
}