#include "Portal.hpp"
#include "fases/Fase.hpp"
#include "gerenciadores/Gerenciador_Colisoes.hpp"

namespace Entidades
{
    Portal::Portal(float posX, float posY, Fases::Fase *pFase) : Entidade({posX, posY}, {70, 110}), pFase(pFase)
    {
        aplicarTextura(Gerenciadores::Portal);
    }

    Portal::~Portal()
    {
    }

    void Portal::salvar()
    {
        salvarDataBuffer();
        nlohmann::json j = nlohmann::json::parse(getBufferDados());
        j["tipo"] = "Portal";
        escreverBuffer(j);
    }

    void Portal::teleportar(Entidades::Personagens::Jogador *pJog)
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