#include "fases/FaseSegunda.hpp"
#include "entidades/obstaculos/Espinhos.hpp"

namespace Fases
{

    FaseSegunda::FaseSegunda(Gerenciadores::Gerenciador_Colisoes *pGC) : Fase(pGC), maxETs(50)
    {
        pFig->setSize({LARGURA - 1, ALTURA - 1});
        pFig->setOrigin({0, 0});
        aplicarTextura(Gerenciadores::FundoFase1);
        criarCenario();
    }

    FaseSegunda::~FaseSegunda()
    {
        posicoesEspinhos.clear();
    }

    void FaseSegunda::criarEspinhos()
    {
        sf::Vector2f tamanhoPadrao(100.0f, 40.0f);

        posicoesEspinhos.push_back(sf::Vector2f(300.0f, 953.0f));
        posicoesEspinhos.push_back(sf::Vector2f(700.0f, 953.0f));
        posicoesEspinhos.push_back(sf::Vector2f(1100.0f, 953.0f));
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

    void FaseSegunda::criarObstaculo()
    {
        criarPlataformas();
        criarEspinhos();
    }

    void FaseSegunda::criarInimigos()
    {
        criarInimFaceis();
    }

    void FaseSegunda::criarProjeteis()
    {
        for (int i = 0; i < 1000; i++)
        {
            Entidades::Projetil *novoProjetil = new Entidades::Projetil(-500.0f, -500.0f, false, 1);
            incluirProjetil(novoProjetil);
        }
    }

    void FaseSegunda::executar()
    {
        Fase::executar();
    }

}