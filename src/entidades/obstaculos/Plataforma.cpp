#include "entidades/obstaculos/Plataforma.hpp"

namespace Entidades
{
    namespace Obstaculos
    {
        Plataforma::Plataforma(int posX, int posY, int tamanhoX, int tamanhoY) : Obstaculo (posX, posY, tamanhoX, tamanhoY), altura(tamanhoY)
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
            
        }

        void Plataforma::executar(Entidades::Personagens::Jogador *p)
        {
            obstaculizar(p);
            desenhar();
        }
    }
}