#include "Portal.hpp"

namespace Entidades
{
    Portal::Portal(float posX, float posY, sf::Color cor) : Entidade({posX, posY}, {40, 80}), cor(cor)
    {
    };

    Portal::~Portal()
    {
    };

    void Portal::salvar()
    {

    };
    
    void Portal::teleportar(Entidades::Personagens::Jogador* pJog)
    {
        if (pJog )
        {

        };
    }

    void Portal::executar()
    {
        aplicarGravidade();
        anularGravidade();
        atualizarPosicao();

        
    }
}