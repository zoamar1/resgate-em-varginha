#include "entidades/obstaculos/Obstaculo.hpp"

namespace Entidades
{
    namespace Obstaculos
    {

        Obstaculo::Obstaculo(float posX, float posY, float tamanhoX, float tamanhoY, bool dano) : 
        Entidade(posX, posY, tamanhoX, tamanhoY, false),
        danoso(dano)
        {
        }

        Obstaculo::~Obstaculo()
        {
            
        }

        void Obstaculo::salvarDataBuffer()
        {
        }
    }
}
