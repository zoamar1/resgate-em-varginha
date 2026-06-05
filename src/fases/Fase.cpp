#include "fases/Fase.hpp"
#include "entidades/obstaculos/Plataforma.hpp"
#include "entidades/personagens/Guarda.hpp"

namespace Fases
{
    Fase::Fase(Gerenciadores::Gerenciador_Colisoes *pGC) : lista_ents(), GC(pGC)
    {
        for (int i = 0; i < 100; i++)
        {
            sf::RectangleShape *vida = new sf::RectangleShape(sf::Vector2f(5, 30));
            vida->setFillColor(sf::Color::Green);
            vida->setPosition(LARGURA - i * 5 - 50, 30);
            barra_de_vida.push_back(vida);
        }
    }
    Fase::~Fase()
    {
        if (GC)
        {
            GC->limparTudo();
        }
        if (GC)
            lista_ents.limparExcetoJogador(GC->getJogador1());
        else
            lista_ents.limparExcetoJogador(NULL);

        for (int i = 0; i < (int)barra_de_vida.size(); i++)
        {
            delete barra_de_vida[i];
        }
        barra_de_vida.clear();

        GC = NULL;
        posicoesInimigosFaceis.clear();
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
        }

        desenhar();
        lista_ents.desenhar();

        if (GC && GC->getJogador1())
        {
            if (GC->getJogador1()->get_vida_atual() > 0)
                desenharBarraDeVida(GC->getJogador1()->get_vida_atual());
        }
    }

    void Fase::criarChao()
    {
        float yChaoBaixo = 990.0f;

        for (float x = 0.0f; x < 1920.0f; x += 200.0f)
        {
            Entidades::Chao *pNovoChao = new Entidades::Chao(sf::Vector2f(x, yChaoBaixo), sf::Vector2f(200.0f, 30.0f));
            if (pNovoChao)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pNovoChao));
                if (GC)
                {
                    GC->incluirChao(pNovoChao);
                }
            }
        }

        for (float x = 250.0f; x <= 1920.0f; x += 200.0f)
        {
            Entidades::Chao *pNovoChao = new Entidades::Chao(sf::Vector2f(x, 250.0f), sf::Vector2f(200.0f, 30.0f));
            if (pNovoChao)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pNovoChao));
                if (GC)
                {
                    GC->incluirChao(pNovoChao);
                }
            }
        }

        for (float x = 0.0f; x <= 1400.0f; x += 200.0f)
        {
            Entidades::Chao *pNovoChao = new Entidades::Chao(sf::Vector2f(x, 620.0f), sf::Vector2f(200.0f, 30.0f));
            if (pNovoChao)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pNovoChao));
                if (GC)
                {
                    GC->incluirChao(pNovoChao);
                }
            }
        }

        Entidades::Chao *pApoioBaixoMedio = new Entidades::Chao(sf::Vector2f(1600.0f, 850.0f), sf::Vector2f(150.0f, 30.0f));
            if (pApoioBaixoMedio)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pApoioBaixoMedio));
                if (GC)
                {
                    GC->incluirChao(pApoioBaixoMedio);
                }
            }

        Entidades::Chao *p2ApoioBaixoMedio = new Entidades::Chao(sf::Vector2f(1700.0f, 725.0f), sf::Vector2f(150.0f, 30.0f));
            if (pApoioBaixoMedio)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(p2ApoioBaixoMedio));
                if (GC)
                {
                    GC->incluirChao(p2ApoioBaixoMedio);
                }
            }

        Entidades::Chao *pApoioMedioCima = new Entidades::Chao(sf::Vector2f(100.0f, 475.0f), sf::Vector2f(150.0f, 30.0f));
            if (pApoioMedioCima)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pApoioMedioCima));
                if (GC)
                {
                    GC->incluirChao(pApoioMedioCima);
                }
            }

        Entidades::Chao *p2ApoioMedioCima = new Entidades::Chao(sf::Vector2f(0.0f, 330.0f), sf::Vector2f(150.0f, 30.0f));
            if (pApoioMedioCima)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(p2ApoioMedioCima));
                if (GC)
                {
                    GC->incluirChao(p2ApoioMedioCima);
                }
            }
    }

    void Fase::criarInimFaceis()
    {
        posicoesInimigosFaceis.push_back(sf::Vector2f(300.0f, 863.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(800.0f, 863.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(1300.0f, 863.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(500.0f, 493.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(1100.0f, 493.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(600.0f, 123.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(900.0f, 123.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(1400.0f, 123.0f));

        int quantidade = (rand() % 3) + 3;

        for (int i = 0; i < quantidade; i++)
        {
            int indiceSorteado = rand() % posicoesInimigosFaceis.size();
            sf::Vector2f posEscolhida = posicoesInimigosFaceis[indiceSorteado];

            Entidades::Personagens::Guarda *pGuarda = new Entidades::Personagens::Guarda(posEscolhida.x, posEscolhida.y, 3, 15, 10);

            if (pGuarda)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pGuarda));

                if (GC)
                {
                    GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo *>(pGuarda));
                }
            }

            posicoesInimigosFaceis.erase(posicoesInimigosFaceis.begin() + indiceSorteado);
        }
    }

    void Fase::criarPlataformas()
    {
        posicoesPlataformas.push_back(sf::Vector2f(400.0f, 110.0f));
        posicoesPlataformas.push_back(sf::Vector2f(950.0f, 110.0f));
        posicoesPlataformas.push_back(sf::Vector2f(1500.0f, 110.0f));
        posicoesPlataformas.push_back(sf::Vector2f(400.0f, 480.0f));
        posicoesPlataformas.push_back(sf::Vector2f(800.0f, 480.0f));
        posicoesPlataformas.push_back(sf::Vector2f(1200.0f, 480.0f));
        posicoesPlataformas.push_back(sf::Vector2f(200.0f, 850.0f));
        posicoesPlataformas.push_back(sf::Vector2f(600.0f, 850.0f));
        posicoesPlataformas.push_back(sf::Vector2f(1000.0f, 850.0f));

        int quantidade = (rand() % 7) + 3;

        sf::Vector2f tamanhoPadrao(200.0f, 30.0f);

        for (int i = 0; i < quantidade; i++)
        {
            int indiceSorteado = rand() % posicoesPlataformas.size();
            sf::Vector2f posEscolhida = posicoesPlataformas[indiceSorteado];

            Entidades::Obstaculos::Plataforma *pPlat = new Entidades::Obstaculos::Plataforma(posEscolhida.x, posEscolhida.y, tamanhoPadrao.x, tamanhoPadrao.y);

            if (pPlat)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pPlat));
                if (GC)
                {
                    GC->incluirObstaculo(pPlat);
                }
            }

            posicoesPlataformas.erase(posicoesPlataformas.begin() + indiceSorteado);
        }
    }
    void Fase::criarCenario()
    {
        criarChao();
        criarObstaculo();
        criarInimigos();
        criarProjeteis();
    }
    void Fase::incluirJogador(Entidades::Personagens::Jogador *pJog1, sf::Vector2f pos)
    {
        if (pJog1)
        {
            pJog1->setPosicao(pos);
            pJog1->setVelocidade(sf::Vector2f(0.0f, 0.0f));
            pJog1->setNoChao(false);
            lista_ents.incluir(pJog1);
        }
    }

    void Fase::incluirProjetil(Entidades::Projetil *pProjetil)
    {
        lista_ents.incluir(pProjetil);
        if (GC)
        {
            GC->incluirProjetil(pProjetil);
        }
    };

    void Fase::desenharBarraDeVida(int vida_atual)
    {
        if (pGG)
        {
            for (int i = 0; i < (int)barra_de_vida.size(); i++)
            {
                if (vida_atual < i)
                {
                    barra_de_vida[i]->setFillColor(sf::Color::Red);
                }
                else
                {
                    barra_de_vida[i]->setFillColor(sf::Color::Green);
                }
                pGG->desenhaRect(*(barra_de_vida[i]));
            }
        }
    }

}