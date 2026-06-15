#include "fases/FaseSegunda.hpp"
#include "entidades/obstaculos/Espinhos.hpp"
#include "entidades/personagens/ET_Varginha.hpp"

namespace Fases
{

    FaseSegunda::FaseSegunda(Gerenciadores::Gerenciador_Colisoes *pGC) : Fase(pGC), maxETs(50)
    {
        pFig->setSize({LARGURA - 1, ALTURA - 1});
        pFig->setOrigin({0, 0});
        aplicarTextura(Gerenciadores::FundoFase2);
        criarCenario();
    }

    FaseSegunda::~FaseSegunda()
    {
        posicoesEspinhos.clear();
        posicoesChefao.clear();
        vetorETs.clear();
    }

    void FaseSegunda::criarEspinhos()
    {
        sf::Vector2f tamanhoPadrao(100.0f, 40.0f);

        posicoesEspinhos.push_back(sf::Vector2f(300.0f, 963.0f));
        posicoesEspinhos.push_back(sf::Vector2f(700.0f, 963.0f));
        posicoesEspinhos.push_back(sf::Vector2f(1100.0f, 1013.0f));
        posicoesEspinhos.push_back(sf::Vector2f(200.0f, 583.0f));
        posicoesEspinhos.push_back(sf::Vector2f(600.0f, 583.0f));
        posicoesEspinhos.push_back(sf::Vector2f(1000.0f, 583.0f));
        posicoesEspinhos.push_back(sf::Vector2f(400.0f, 213.0f));
        posicoesEspinhos.push_back(sf::Vector2f(800.0f, 213.0f));
        posicoesEspinhos.push_back(sf::Vector2f(1200.0f, 213.0f));

        int quantidade = (rand() % 4) + 3;

        for (int i = 0; i < quantidade; i++)
        {
            if (posicoesEspinhos.empty())
                break;

            int indiceSorteado = rand() % posicoesEspinhos.size();
            sf::Vector2f posEscolhida = posicoesEspinhos[indiceSorteado];

            Entidades::Obstaculos::Espinhos *pEspinho = new Entidades::Obstaculos::Espinhos(posEscolhida.x, posEscolhida.y, tamanhoPadrao.x, tamanhoPadrao.y, 2);

            if (pEspinho)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pEspinho));
                if (GC)
                {
                    GC->incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo *>(pEspinho));
                }
            }

            posicoesEspinhos.erase(posicoesEspinhos.begin() + indiceSorteado);
        }
    }

    void FaseSegunda::criaChefao()
    {
        posicoesChefao.push_back(sf::Vector2f(100.0f, 863.0f));
        posicoesChefao.push_back(sf::Vector2f(700.0f, 863.0f));
        posicoesChefao.push_back(sf::Vector2f(1200.0f, 863.0f));
        posicoesChefao.push_back(sf::Vector2f(200.0f, 493.0f));
        posicoesChefao.push_back(sf::Vector2f(1100.0f, 493.0f));
        posicoesChefao.push_back(sf::Vector2f(450.0f, 123.0f));
        posicoesChefao.push_back(sf::Vector2f(600.0f, 123.0f));
        posicoesChefao.push_back(sf::Vector2f(1100.0f, 123.0f));

        int quantidade = (rand() % 3) + 3;

        for (int i = 0; i < quantidade; i++)
        {
            int indiceSorteado = rand() % posicoesChefao.size();
            sf::Vector2f posEscolhida = posicoesChefao[indiceSorteado];

            Entidades::Personagens::ET_Varginha *pChefao = new Entidades::Personagens::ET_Varginha(posEscolhida.x, posEscolhida.y, 3, 15, 1);

            if (pChefao)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pChefao));

                vetorETs.push_back(pChefao);

                if (GC)
                {
                    GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo *>(pChefao));
                }
            }

            posicoesChefao.erase(posicoesChefao.begin() + indiceSorteado);
        }
    }

    void FaseSegunda::criarObstaculo()
    {
        criarPlataformas();
        criarEspinhos();
        criarPortal(1750.0f, 110.0f, sf::Color::Cyan); 
    }

    void FaseSegunda::criarInimigos()
    {
        criarInimFaceis();
        criaChefao();
    }

    void FaseSegunda::criarProjeteis()
    {
        for (int i = 0; i < 50; i++)
        {
            Entidades::Projetil *novoProjetil = new Entidades::Projetil(-500.0f, -500.0f, false, 1);
            incluirProjetil(novoProjetil);
        }
    }

    void FaseSegunda::executar()
    {
        for (auto it = vetorETs.begin(); it != vetorETs.end();)
        {
            if (*it == NULL || (*it)->get_vida_atual() <= 0)
            {
                it = vetorETs.erase(it);
            }
            else
            {
                it++;
            }
        }

        for (int i = 0; i < (int)vetorETs.size(); i++)
        {
            Entidades::Personagens::ET_Varginha *pET = vetorETs[i];
            if (pET && pET->getQuerAtirar())
            {
                Entidades::Projetil *pProjetil = getProjetilDisponivel();
                if (pProjetil)
                {
                    pET->atirar(pProjetil);
                }
            }
        }

        Fase::executar();
    }

}