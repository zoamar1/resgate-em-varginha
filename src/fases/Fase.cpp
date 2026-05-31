#include "fases/Fase.hpp"
#include "entidades/obstaculos/Plataforma.hpp"
#include "entidades/personagens/Guarda.hpp"

namespace Fases
{
    Fase::Fase(Gerenciadores::Gerenciador_Colisoes *pGC) : lista_ents(), GC(pGC), pChao(NULL)
    {
    }
    Fase::~Fase()
    {
        GC = NULL;
        pChao = NULL;
    }
    void Fase::criarChao()
    {
        if (!pChao)
        {
            pChao = new Entidades::Chao();
            lista_ents.incluir(pChao);
        }
    }
    void Fase::executar()
    {
        lista_ents.percorrer();

        if (GC)
        {
            if (GC->getJogador1())
            {
                GC->getJogador1()->setNoChao(false);
            }

            GC->executar();

            if (pChao)
            {
                GC->colisaoJogadorChao(pChao);
                GC->colisaoInimigoChao(pChao);
            }
        }

        lista_ents.desenhar();
    }

    void Fase::criarInimFaceis(sf::Vector2f pos)
    {
        Entidades::Personagens::Guarda *pGuarda = new Entidades::Personagens::Guarda(pos.x, pos.y, 3, 15, 10);

        if (pGuarda)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade *>(pGuarda));

            if (GC)
            {
                GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo *>(pGuarda));
            }
        }
    }

    void Fase::criarPlataformas(const sf::Vector2f pos, const sf::Vector2f tam)
    {
        Entidades::Obstaculos::Plataforma *pPlat = new Entidades::Obstaculos::Plataforma(pos.x, pos.y, tam.x, tam.y);

        if (pPlat)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade *>(pPlat));
            if (GC)
            {
                GC->incluirObstaculo(pPlat);
            }
        }
    }
    void Fase::criarCenario()
    {
        criarChao();
        criarObstaculo();
        criarInimigos();
    }
    void Fase::incluirJogador(Entidades::Personagens::Jogador *pJog1)
    {
        lista_ents.incluir(pJog1);
    }
}