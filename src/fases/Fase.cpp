#include "fases/Fase.hpp"
#include "entidades/obstaculos/Plataforma.hpp"
#include "entidades/personagens/Guarda.hpp"
#include "entidades/personagens/Exercito.hpp"
#include "entidades/Portal.hpp"

namespace Fases
{
    Fase::Fase(Gerenciadores::Gerenciador_Colisoes *pGC) : lista_ents(), GC(pGC), faseConcluida(false)
    {
        for (int i = 0; i < 2; i++)
        {
            sf::RectangleShape *vida = new sf::RectangleShape(sf::Vector2f(500, 30));
            (i % 2) ? vida->setFillColor(sf::Color::Green) : vida->setFillColor(sf::Color::Red);
            vida->setPosition(LARGURA - 550, 30);
            barra_de_vida.push_back(vida);
        }

        for (int i = 0; i < 2; i++)
        {
            sf::RectangleShape *vida = new sf::RectangleShape(sf::Vector2f(500, 30));
            (i % 2) ? vida->setFillColor(sf::Color::Green) : vida->setFillColor(sf::Color::Red);
            vida->setPosition(50, 30);
            barra_de_vida.push_back(vida);
        }
    }

    Fase::~Fase()
    {
        if (GC)
        {
            GC->limparTudo();
        }

        lista_ents.limparExcetoJogadores();

        for (int i = 0; i < (int)barra_de_vida.size(); i++)
        {
            delete barra_de_vida[i];
        }
        barra_de_vida.clear();

        ProjeteisPossiveis.clear();

        GC = NULL;
        posicoesInimigosFaceis.clear();
    }

    void Fase::executar()
    {
        lista_ents.percorrer();

        if (GC)
        {
            const std::vector<Entidades::Personagens::Jogador *> &jogadores = GC->getJogadores();
            for (int i = 0; i < (int)jogadores.size(); i++)
            {
                if (jogadores[i])
                {
                    jogadores[i]->setNoChao(false);
                }
            }

            GC->executar();
        }

        desenhar();
        lista_ents.desenhar();

        if (GC)
        {
            const std::vector<Entidades::Personagens::Inimigo *> &inimigos = GC->getInimigos();
            for (int i = 0; i < (int)inimigos.size(); i++)
            {
                Entidades::Personagens::Exercito *pExercito = dynamic_cast<Entidades::Personagens::Exercito *>(inimigos[i]);
                if (pExercito)
                {
                    pExercito->desenharExplosao();
                }
            }
        }

        lista_ents.removerMortos(GC);

        if (GC)
        {
            const std::vector<Entidades::Personagens::Jogador *> &jogadores = GC->getJogadores();
            for (int i = 0; i < (int)jogadores.size(); i++)
            {
                if (jogadores[i] && jogadores[i]->get_vida_atual() > 0)
                {
                    desenharBarraDeVida(jogadores[i], i);
                }
            }
        }
    }

    Entidades::Projetil *Fase::getProjetilDisponivel()
    {
        for (int i = 0; i < (int)ProjeteisPossiveis.size(); i++)
        {
            if (ProjeteisPossiveis[i] && !ProjeteisPossiveis[i]->getAtivo())
            {
                return ProjeteisPossiveis[i];
            }
        }
        return NULL;
    }

    bool Fase::getFaseConcluida() const
    {
        return faseConcluida;
    }

    void Fase::setFaseConcluida(bool c)
    {
        faseConcluida = c;
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
        if (p2ApoioBaixoMedio)
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
        if (p2ApoioMedioCima)
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

            Entidades::Personagens::Guarda *pGuarda = new Entidades::Personagens::Guarda(posEscolhida.x, posEscolhida.y, 3, 15, 3);

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

    void Fase::criarPortal(float posX, float posY, sf::Color cor)
    {
        Entidades::Portal* pPortal = new Entidades::Portal(posX, posY, this, cor); 
        if (pPortal)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade*>(pPortal));
            if (GC)
            {
                GC->incluirPortal(pPortal);
            }
        }
    }

    void Fase::incluirJogador(Entidades::Personagens::Jogador *pJogador, sf::Vector2f pos)
    {
        if (pJogador)
        {
            pJogador->setPosicao(pos);
            pJogador->setVelocidade(sf::Vector2f(0.0f, 0.0f));
            pJogador->setNoChao(false);
            lista_ents.incluir(pJogador);
        }
    }

    void Fase::incluirProjetil(Entidades::Projetil *pProjetil)
    {
        if (pProjetil)
        {
            lista_ents.incluir(pProjetil);
            ProjeteisPossiveis.push_back(pProjetil);
            if (GC)
            {
                GC->incluirProjetil(pProjetil);
            }
        }
    }

    void Fase::desenharBarraDeVida(Entidades::Personagens::Jogador *pJog, int indiceJogador)
    {
        if (pGG)
        {
            int base = indiceJogador * 2;

            if ((int)barra_de_vida.size() < base + 2)
            {
                return;
            }

            sf::RectangleShape *fundo = barra_de_vida[base];
            sf::RectangleShape *vida = barra_de_vida[base + 1];
            float tamFundoX = fundo->getSize().x;
            float vida_atual = static_cast<float>(pJog->get_vida_atual());
            float vida_total = static_cast<float>(pJog->get_num_vidas());

            vida->setSize({(tamFundoX / vida_total) * vida_atual, vida->getSize().y});

            pGG->desenhaRect(*fundo);
            pGG->desenhaRect(*vida);
        }
    }

}