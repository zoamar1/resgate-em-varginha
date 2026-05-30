#include "entidades/obstaculos/Espinhos.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Espinhos::Espinhos(float posX, float posY, float tamanhoX, float tamanhoY, short int dano) : Obstaculo(posX, posY, tamanhoX, tamanhoY), danosidade(dano)
        {
        }

        Espinhos::~Espinhos()
        {
        }

        void Espinhos::salvar()
        {
        }

        void Espinhos::obstaculizar(Entidades::Personagens::Jogador *p)
        {
            if (p)
            {
                p->recebeDano(danosidade);
            }
        }

        void Espinhos::executar(Entidades::Personagens::Jogador *p)
        {
            obstaculizar(p);
            desenhar();
        }
    }
}