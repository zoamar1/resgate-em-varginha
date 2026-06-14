#include "Portal.hpp"
#include "fases/Fase.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"

namespace Entidades
{
    Portal::Portal(float posX, float posY, Fases::Fase* pFase, sf::Color cor) : Entidade({posX, posY}, {70, 110}), cor(cor), pFase(pFase)
    {
        aplicarTextura(Gerenciadores::Portal);
    };

    Portal::~Portal()
    {
    };

    void Portal::salvar()
    {

    };
    
    void Portal::teleportar(Entidades::Personagens::Jogador* pJog)
    {
        if (pJog && pFase)
        {
            pFase->setFaseConcluida(true);
        }
    }

    void Portal::executar()
    {
        aplicarGravidade();
        anularGravidade();
        atualizarPosicao();
    }
}