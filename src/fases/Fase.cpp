#include "fases/Fase.hpp"
#include "entidades/obstaculos/Plataforma.hpp"
#include "entidades/personagens/Guarda.hpp"

namespace Fases
{
    Fase::Fase(Gerenciadores::Gerenciador_Colisoes *pGC) : lista_ents(), GC(pGC), pChao(NULL), vChaos()
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

        pChao = NULL;
        if (GC)
            lista_ents.limparExcetoJogador(GC->getJogador1());
        else
            lista_ents.limparExcetoJogador(NULL);

        vChaos.clear();

        for (int i = 0; i < (int)barra_de_vida.size(); i++)
        {
            delete barra_de_vida[i];
        }
        barra_de_vida.clear();

        GC = NULL;
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
                vChaos.push_back(pNovoChao);

                if (!pChao)
                {
                    pChao = pNovoChao;
                }
            }
        }

        for (float x = 250.0f; x <= 1920.0f; x += 200.0f)
        {
            Entidades::Chao *pNovoChao = new Entidades::Chao(sf::Vector2f(x, 250.0f), sf::Vector2f(200.0f, 30.0f));
            if (pNovoChao)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pNovoChao));
                vChaos.push_back(pNovoChao);
            }
        }

        for (float x = 0.0f; x <= 1400.0f; x += 200.0f)
        {
            Entidades::Chao *pNovoChao = new Entidades::Chao(sf::Vector2f(x, 620.0f), sf::Vector2f(200.0f, 30.0f));
            if (pNovoChao)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pNovoChao));
                vChaos.push_back(pNovoChao);
            }
        }

        Entidades::Chao *pApoioBaixoMedio = new Entidades::Chao(sf::Vector2f(1600.0f, 850.0f), sf::Vector2f(150.0f, 30.0f));
        if (pApoioBaixoMedio)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade *>(pApoioBaixoMedio));
            vChaos.push_back(pApoioBaixoMedio);
        }

        Entidades::Chao *p2ApoioBaixoMedio = new Entidades::Chao(sf::Vector2f(1700.0f, 725.0f), sf::Vector2f(150.0f, 30.0f));
        if (pApoioBaixoMedio)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade *>(p2ApoioBaixoMedio));
            vChaos.push_back(p2ApoioBaixoMedio);
        }

        Entidades::Chao *pApoioMedioCima = new Entidades::Chao(sf::Vector2f(100.0f, 465.0f), sf::Vector2f(150.0f, 30.0f));
        if (pApoioMedioCima)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade *>(pApoioMedioCima));
            vChaos.push_back(pApoioMedioCima);
        }

        Entidades::Chao *p2ApoioMedioCima = new Entidades::Chao(sf::Vector2f(0.0f, 330.0f), sf::Vector2f(150.0f, 30.0f));
        if (pApoioMedioCima)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade *>(p2ApoioMedioCima));
            vChaos.push_back(p2ApoioMedioCima);
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

            std::vector<Entidades::Chao *>::iterator it;

            for (it = vChaos.begin(); it < vChaos.end(); it++)
            {
                if (*it)
                {
                    GC->colisaoJogadorChao(*it);
                    GC->colisaoInimigoChao(*it);
                }
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