#include "entidades/obstaculos/Obstaculo.hpp"

namespace Entidades
{
    namespace Obstaculos
    {

        Obstaculo::Obstaculo(int posX, int posY, int tamanhoX, int tamanhoY, bool danoso) : Entidade(posX, posY, tamanhoX, tamanhoY),
                                                                                            danoso(danoso)
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
