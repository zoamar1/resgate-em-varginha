#include "fases/Fase.hpp"
#include "entidades/obstaculos/Plataforma.hpp"
#include "entidades/personagens/Guarda.hpp"
#include "entidades/personagens/Exercito.hpp"
#include "entidades/Portal.hpp"
#include "entidades/obstaculos/Arbusto.hpp"
#include "entidades/obstaculos/Espinhos.hpp"

namespace Fases
{
    Fase::Fase(Gerenciadores::Gerenciador_Colisoes *pGC) : minInimFaceis(3), maxInimFaceis(5), minPlataformas(3), maxPlataformas(9), lista_ents(), GC(pGC), faseConcluida(false)
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
            GC->limparColisoes();
        }

        lista_ents.limparExcetoJogadores();

        for (int i = 0; i < (int)barra_de_vida.size(); i++)
        {
            delete barra_de_vida[i];
        }
        barra_de_vida.clear();

        ProjeteisPossiveis.clear();
        projeteisPendentesDono.clear();

        GC = NULL;
        posicoesInimigosFaceis.clear();
        posicoesPlataformas.clear();
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

        desenharCena();
    }

    void Fase::desenharCena()
    {
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

    std::vector<std::string> Fase::coletarDadosSalvamento()
    {
        return lista_ents.coletarDadosSalvamento();
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
        dividirChao({0, 1000}, {1920, 30});
        dividirChao({250, 250}, {1920, 30});
        dividirChao({250, 250}, {1670, 30});
        dividirChao({0, 620}, {1520, 30});
        dividirChao({1550, 860}, {150, 30});
        dividirChao({1650, 725}, {150, 30});
        dividirChao({50, 475}, {150, 30});
        dividirChao({0, 330}, {150, 30});
    }

    void Fase::dividirChao(sf::Vector2f pos, sf::Vector2f tam)
    {
        float divisaoX = 32.0f;
        float divisaoY = 32.0f;

        for (float x = 0.0f; x < tam.x; x += divisaoX)
        {
            Entidades::Chao *pNovoChao = new Entidades::Chao({pos.x + x, pos.y}, {divisaoX, divisaoY});
            if (pNovoChao)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pNovoChao));
                if (GC)
                {
                    GC->incluirChao(pNovoChao);
                }
            }
        }
    }

    void Fase::criarInimFaceis()
    {
        posicoesInimigosFaceis.clear();
        posicoesInimigosFaceis.push_back(sf::Vector2f(300.0f, 863.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(800.0f, 863.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(1300.0f, 863.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(500.0f, 493.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(1100.0f, 493.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(600.0f, 123.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(900.0f, 123.0f));
        posicoesInimigosFaceis.push_back(sf::Vector2f(1400.0f, 123.0f));

        int quantidade = (rand() % (maxInimFaceis - minInimFaceis + 1)) + minInimFaceis;

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
        posicoesPlataformas.push_back(sf::Vector2f(200.0f, 860.0f));
        posicoesPlataformas.push_back(sf::Vector2f(600.0f, 860.0f));
        posicoesPlataformas.push_back(sf::Vector2f(1000.0f, 860.0f));

        int quantidade = (rand() % (maxPlataformas - minPlataformas + 1)) + minPlataformas;

        sf::Vector2f tamanhoPadrao(200.0f, 30.0f);

        for (int i = 0; i < quantidade; i++)
        {
            int indiceSorteado = rand() % posicoesPlataformas.size();
            sf::Vector2f posEscolhida = posicoesPlataformas[indiceSorteado];
            dividirPlataforma(posEscolhida, tamanhoPadrao);
            posicoesPlataformas.erase(posicoesPlataformas.begin() + indiceSorteado);
        }
    }

    void Fase::dividirPlataforma(sf::Vector2f pos, sf::Vector2f tam)
    {
        float divisaoX = 32.0f;
        float divisaoY = 32.0f;

        for (float x = 0.0f; x < tam.x; x += divisaoX)
        {
            Entidades::Obstaculos::Plataforma *pPlat = new Entidades::Obstaculos::Plataforma(pos.x + x, pos.y, divisaoX, divisaoY);
            if (pPlat)
            {
                lista_ents.incluir(static_cast<Entidades::Entidade *>(pPlat));
                if (GC)
                {
                    GC->incluirObstaculo(pPlat);
                }
            }
        }
    }

    void Fase::criarCenario()
    {
        criarChao();
        criarObstaculo();
        criarInimigos();
        criarProjeteis();
    }

    void Fase::criarPortal(float posX, float posY)
    {
        Entidades::Portal *pPortal = new Entidades::Portal(posX, posY, this);
        if (pPortal)
        {
            lista_ents.incluir(static_cast<Entidades::Entidade *>(pPortal));
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

    void Fase::carregarCenario(const std::vector<std::string> &dadosCenario)
    {
        criarChao();
        criarProjeteis();

        for (size_t i = 0; i < dadosCenario.size(); i++)
        {
            try
            {
                nlohmann::json j = nlohmann::json::parse(dadosCenario[i]);
                std::string tipo = j.value("tipo", "");
                float posX = j.value("posX", 0.0f);
                float posY = j.value("posY", 0.0f);

                if (tipo == "Plataforma")
                {
                    float altura = j.value("altura", 32.0f);
                    Entidades::Obstaculos::Plataforma *pPlat =
                        new Entidades::Obstaculos::Plataforma(posX, posY, 32.0f, altura);
                    lista_ents.incluir(static_cast<Entidades::Entidade *>(pPlat));
                    if (GC)
                        GC->incluirObstaculo(pPlat);
                }
                else if (tipo == "Arbusto")
                {
                    float largura = j.value("largura", 100.0f);
                    float altura = j.value("altura", 40.0f);
                    Entidades::Obstaculos::Arbusto *pArbusto =
                        new Entidades::Obstaculos::Arbusto(posX, posY, largura, altura);
                    lista_ents.incluir(static_cast<Entidades::Entidade *>(pArbusto));
                    if (GC)
                        GC->incluirObstaculo(pArbusto);
                }
                else if (tipo == "Espinhos")
                {
                    float tamX = j.value("tamanhoX", 100.0f);
                    float tamY = j.value("tamanhoY", 40.0f);
                    short int dano = (short int)j.value("danosidade", 2);
                    Entidades::Obstaculos::Espinhos *pEsp =
                        new Entidades::Obstaculos::Espinhos(posX, posY, tamX, tamY, dano);
                    lista_ents.incluir(static_cast<Entidades::Entidade *>(pEsp));
                    if (GC)
                        GC->incluirObstaculo(pEsp);
                }
                else if (tipo == "Guarda")
                {
                    int vidaAtual = j.value("vida_atual", 0);
                    if (vidaAtual > 0)
                    {
                        int numVidas = j.value("num_vidas", 3);
                        int forca = j.value("forca", 3);
                        int maldade = j.value("nivel_maldade", 15);
                        float posIniX = j.value("posicaoInicialX", posX);
                        float posIniY = j.value("posicaoInicialY", posY);

                        Entidades::Personagens::Guarda *pG =
                            new Entidades::Personagens::Guarda(posX, posY, numVidas, maldade, forca);
                        pG->set_vida_atual(vidaAtual);
                        pG->setPosicaoInicial(sf::Vector2f(posIniX, posIniY));
                        lista_ents.incluir(static_cast<Entidades::Entidade *>(pG));
                        if (GC)
                            GC->incluirInimigo(static_cast<Entidades::Personagens::Inimigo *>(pG));
                    }
                }
                else if (tipo == "Projetil")
                {
                    bool ativo = j.value("ativo", false);
                    if (ativo)
                    {
                        int dano = j.value("dano", 0);
                        bool deJogador = j.value("deJogador", false);
                        float velX = j.value("velX", 0.0f);
                        float velY = j.value("velY", 0.0f);
                        int idDonoJogador = j.value("idDonoJogador", -1);
                        int idAlienDono = j.value("idAlienDono", -1);

                        Entidades::Projetil *pProj = new Entidades::Projetil(posX, posY, true, dano);
                        pProj->setDeJogador(deJogador);
                        pProj->setVelocidade(sf::Vector2f(velX, velY));
                        incluirProjetil(pProj);

                        if (idDonoJogador > 0)
                        {
                            projeteisPendentesDono.push_back(std::make_pair(pProj, idDonoJogador));
                        }

                        if (idAlienDono >= 0)
                        {
                            relacionarProjetilAlien(pProj, idAlienDono);
                        }
                    }
                }
                else
                {
                    carregarInimigoEspecial(dadosCenario[i]);
                }
            }
            catch (...)
            {
                std::cerr << "Erro ao carregar entidade salva do cenario." << std::endl;
            }
        }

        criarPortal(1750.0f, 110.0f);
    }

    void Fase::relacionarProjetilAlien(Entidades::Projetil *pProj, int idAlienSalvo)
    {
        (void)pProj;
        (void)idAlienSalvo;
    }

    void Fase::vincularDonosProjeteis(Entidades::Personagens::Jogador *pJog1, Entidades::Personagens::Jogador *pJog2)
    {
        for (size_t i = 0; i < projeteisPendentesDono.size(); i++)
        {
            Entidades::Projetil *pProj = projeteisPendentesDono[i].first;
            int idx = projeteisPendentesDono[i].second;

            Entidades::Personagens::Jogador *pDono = NULL;
            if (idx == 1)
                pDono = pJog1;
            else if (idx == 2)
                pDono = pJog2;

            if (pProj && pDono && GC)
            {
                GC->registrarProjetilJogador(pProj, pDono);
                pProj->setIdDonoJogador(idx);
            }
        }
        projeteisPendentesDono.clear();
    }
}