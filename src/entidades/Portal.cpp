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

        // jogar isso aq no gerenciador de colisoes? 

        Gerenciadores::Gerenciador_Colisoes* pGC = Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes();
        if (pGC)
        {
            const std::vector<Entidades::Personagens::Jogador*>& jogadores = pGC->getJogadores();
            for (int i = 0; i < (int)jogadores.size(); i++)
            {
                Entidades::Personagens::Jogador* pJog = jogadores[i];
                if (pJog)
                {
                    sf::Vector2f posPortal = getPosicao();
                    sf::Vector2f tamPortal = getpFig()->getSize();
                    sf::Vector2f posJogador = pJog->getPosicao();
                    sf::Vector2f tamJogador = pJog->getpFig()->getSize();

                    if (posPortal.x < posJogador.x + tamJogador.x && posPortal.x + tamPortal.x > posJogador.x && posPortal.y < posJogador.y + tamJogador.y && posPortal.y + tamPortal.y > posJogador.y) teleportar(pJog);
                }
            }
        }
    }
}