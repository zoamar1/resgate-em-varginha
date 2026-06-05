#include "entidades/obstaculos/Obstaculo.hpp"

namespace Entidades
{
    namespace Obstaculos
    {

        Obstaculo::Obstaculo(float posX, float posY, float tamanhoX, float tamanhoY, bool danoso) : Entidade(sf::Vector2f(posX, posY), sf::Vector2f(tamanhoX, tamanhoY)),
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
