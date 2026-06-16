#include "Jogo.hpp"
#include <sstream>

Jogo::Jogo()
    : pGG(Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()),
      pGE(Gerenciadores::Gerenciador_Eventos::getGerenciador_Eventos(this)),
      pGC(Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes()),
      estado(MENU),
      pMenu(NULL),
      modo2Jogadores(false),
      pJog1(NULL),
      pJog2(NULL),
      pFase1(NULL),
      pFase2(NULL),
      fontePlacarCarregada(false)
{
    Ente::setGG(pGG);
    pGE->setGerenciador_Grafico(pGG);
    pMenu = new Menu();
    pMenu->setJogo(this);

    if (fontePlacar.loadFromFile("assets/fonts/AlfaSlabOne-Regular.ttf"))
        fontePlacarCarregada = true;
}

Jogo::~Jogo()
{
    if (pFase1)
        delete pFase1;
    if (pFase2)
        delete pFase2;
    if (pMenu)
        delete pMenu;
    if (pJog1)
        delete pJog1;
    if (pJog2)
        delete pJog2;
}

void Jogo::iniciarFase1()
{
    if (pFase1)
    {
        delete pFase1;
        pFase1 = NULL;
    }

    if (pGC)
    {
        pGC->limparColisoes();
    }

    pFase1 = new Fases::FasePrimeira(pGC);

    pFase1->incluirJogador(pJog1, sf::Vector2f(100.0f, ALTURA - 100));
    if (pGC)
        pGC->incluirJogador(pJog1);

    if (modo2Jogadores && pJog2)
    {
        pFase1->incluirJogador(pJog2, sf::Vector2f(200.0f, ALTURA - 100));
        if (pGC)
            pGC->incluirJogador(pJog2);
    }
}

void Jogo::iniciarFase2()
{
    if (pFase2)
    {
        delete pFase2;
        pFase2 = NULL;
    }

    if (pGC)
    {
        pGC->limparColisoes();
    }

    pFase2 = new Fases::FaseSegunda(pGC);

    pFase2->incluirJogador(pJog1, sf::Vector2f(100.0f, ALTURA - 100));
    if (pGC)
        pGC->incluirJogador(pJog1);

    if (modo2Jogadores && pJog2)
    {
        pFase2->incluirJogador(pJog2, sf::Vector2f(200.0f, ALTURA - 100));
        if (pGC)
            pGC->incluirJogador(pJog2);
    }
}

void Jogo::salvarRanking()
{
    std::vector<std::pair<std::string, int>> novas;
    if (pJog1)
        novas.push_back({pJog1->getNome(), pJog1->getPontos()});
    if (modo2Jogadores && pJog2)
        novas.push_back({pJog2->getNome(), pJog2->getPontos()});
    Ranking::salvar(novas);
}

void Jogo::desenharPlacar()
{
    if (!fontePlacarCarregada || !pGG)
        return;

    auto desenhaInfo = [&](Entidades::Personagens::Jogador *pJog, float posX, float posY)
    {
        if (!pJog || pJog->get_vida_atual() <= 0)
            return;
        std::ostringstream ss;
        ss << pJog->getNome() << ": " << pJog->getPontos() << " pts";
        sf::Text t;
        t.setFont(fontePlacar);
        t.setString(ss.str());
        t.setCharacterSize(28);
        t.setFillColor(sf::Color::White);
        t.setPosition(posX, posY);
        pGG->desenhaTexto(t);
    };

    desenhaInfo(pJog1, 50.0f, 68.0f);
    if (modo2Jogadores)
        desenhaInfo(pJog2, LARGURA - 570.0f, 68.0f);
}

void Jogo::executar()
{
    if (!pGG || !pGE)
        return;

    while (pGG->janelaAberta())
    {
        sf::Event evento;
        while (pGG->getWindow()->pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                pGG->fecharJanela();

            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
            {
                if (estado == RANKING_TELA || estado == SUB_SELECAO_MODO || estado == SUB_CONTINUAR_JOGO)
                {
                    estado = MENU;
                    pMenu->setTela(TelaMenu::PRINCIPAL);
                    continue;
                }
                else if (estado == SUB_SELECAO_FASE)
                {
                    estado = MENU;
                    pMenu->setTela(TelaMenu::PRINCIPAL);
                    continue;
                }
                else if (estado == CADASTRO_J1 || estado == CADASTRO_J1_2P)
                {
                    estado = SUB_SELECAO_MODO;
                    pMenu->setTela(TelaMenu::SELECAO_MODO);
                    continue;
                }
                else if (estado == CADASTRO_J2)
                {
                    estado = CADASTRO_J1_2P;
                    pMenu->iniciarCadastro(1);
                    continue;
                }
                else if (estado == FASE1 || estado == FASE2)
                {
                    estado = MENU;
                    pMenu->setTela(TelaMenu::PRINCIPAL);
                    continue;
                }

                pGG->fecharJanela();
            }

            if (estado == CADASTRO_J1 || estado == CADASTRO_J1_2P || estado == CADASTRO_J2)
            {
                if (evento.type == sf::Event::TextEntered)
                {
                    sf::Uint32 c = evento.text.unicode;
                    if (c == 8)
                        pMenu->apagarUltimoChar();
                    else if (c != 13)
                        pMenu->processarEventoTexto(c);
                }

                if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Return)
                {
                    pMenu->confirmarNome();
                    std::string nome = pMenu->getNomeDigitado();

                    if (estado == CADASTRO_J1)
                    {
                        if (pJog1)
                        {
                            delete pJog1;
                            pJog1 = NULL;
                        }
                        pJog1 = new Entidades::Personagens::Jogador(500, 0);
                        pJog1->setNome(nome);
                        pGE->setJogador1(pJog1);
                        pGE->setJogador2(NULL);
                        modo2Jogadores = false;

                        estado = SUB_SELECAO_FASE;
                        pMenu->setTela(TelaMenu::SELECAO_FASE);
                    }
                    else if (estado == CADASTRO_J1_2P)
                    {
                        if (pJog1)
                        {
                            delete pJog1;
                            pJog1 = NULL;
                        }
                        pJog1 = new Entidades::Personagens::Jogador(500, 0);
                        pJog1->setNome(nome);
                        pGE->setJogador1(pJog1);
                        modo2Jogadores = true;

                        pMenu->iniciarCadastro(2);
                        estado = CADASTRO_J2;
                    }
                    else if (estado == CADASTRO_J2)
                    {
                        if (pJog2)
                        {
                            delete pJog2;
                            pJog2 = NULL;
                        }
                        pJog2 = new Entidades::Personagens::Jogador(500, 0);
                        pJog2->setNome(nome);
                        pGE->setJogador2(pJog2);

                        estado = SUB_SELECAO_FASE;
                        pMenu->setTela(TelaMenu::SELECAO_FASE);
                    }
                }
                continue;
            }

            if (evento.type == sf::Event::KeyPressed)
            {
                if (estado == MENU)
                {
                    if (evento.key.code == sf::Keyboard::Num1)
                    {
                        estado = SUB_CONTINUAR_JOGO;
                        pMenu->setTela(TelaMenu::CONTINUAR_JOGO);
                    }
                    else if (evento.key.code == sf::Keyboard::Num2)
                    {
                        estado = SUB_SELECAO_MODO;
                        pMenu->setTela(TelaMenu::SELECAO_MODO);
                    }
                    else if (evento.key.code == sf::Keyboard::Num3)
                    {
                        estado = RANKING_TELA;
                        pMenu->setTela(TelaMenu::RANKING);
                    }
                }
                else if (estado == SUB_SELECAO_MODO)
                {
                    if (evento.key.code == sf::Keyboard::Num1)
                    {
                        modo2Jogadores = false;
                        if (pJog2)
                        {
                            delete pJog2;
                            pJog2 = NULL;
                        }
                        pMenu->iniciarCadastro(1);
                        estado = CADASTRO_J1;
                    }
                    else if (evento.key.code == sf::Keyboard::Num2)
                    {
                        modo2Jogadores = true;
                        pMenu->iniciarCadastro(1);
                        estado = CADASTRO_J1_2P;
                    }
                }
                else if (estado == SUB_CONTINUAR_JOGO)
                {
                    if (pJog1 && evento.key.code == sf::Keyboard::Num1)
                    {
                        pJog1->set_vida_atual(pJog1->get_num_vidas());
                        if (pJog2)
                            pJog2->set_vida_atual(pJog2->get_num_vidas());

                        pGE->setJogador1(pJog1);
                        pGE->setJogador2(modo2Jogadores ? pJog2 : NULL);

                        estado = SUB_SELECAO_FASE;
                        pMenu->setTela(TelaMenu::SELECAO_FASE);
                    }
                }
                else if (estado == SUB_SELECAO_FASE)
                {
                    if (evento.key.code == sf::Keyboard::Num1)
                    {
                        estado = FASE1;
                        iniciarFase1();
                    }
                    else if (evento.key.code == sf::Keyboard::Num2)
                    {
                        estado = FASE2;
                        iniciarFase2();
                    }
                }
            }

            if (estado == FASE1 || estado == FASE2)
            {
                pGE->verificaTeclaPressionada(evento);
            }
        }

        if (estado == FASE1 || estado == FASE2)
        {
            pGE->executar();
        }

        pGG->limpaJanela();
        Fases::Fase *faseDeletada = NULL;

        switch (estado)
        {
        case MENU:
        case SUB_SELECAO_MODO:
        case SUB_CONTINUAR_JOGO:
        case SUB_SELECAO_FASE:
        case CADASTRO_J1:
        case CADASTRO_J1_2P:
        case CADASTRO_J2:
        case RANKING_TELA:
            pMenu->executar();
            break;

        case FASE1:
            if (!pFase1)
                iniciarFase1();

            pFase1->executar();
            desenharPlacar();

            if (pFase1->getFaseConcluida())
            {
                delete pFase1;
                pFase1 = NULL;

                faseDeletada = NULL;

                estado = FASE2;
                iniciarFase2();
            }
            else if ((pJog1 && pJog1->get_vida_atual() <= 0) || (modo2Jogadores && pJog2 && pJog2->get_vida_atual() <= 0))
            {
                salvarRanking();
                faseDeletada = pFase1;
                pFase1 = NULL;
                estado = MENU;
                pMenu->setTela(TelaMenu::PRINCIPAL);
            }
            break;

        case FASE2:
            if (!pFase2)
                iniciarFase2();
            pFase2->executar();
            desenharPlacar();

            if (pFase2->getFaseConcluida() || (pJog1 && pJog1->get_vida_atual() <= 0) || (modo2Jogadores && pJog2 && pJog2->get_vida_atual() <= 0))
            {
                salvarRanking();
                faseDeletada = pFase2;
                pFase2 = NULL;
                estado = MENU;
                pMenu->setTela(TelaMenu::PRINCIPAL);
            }
            break;
        }

        pGG->desenhaJanela();
        if (faseDeletada)
        {
            delete faseDeletada;
            faseDeletada = NULL;
        }
    }
}

Jogo::Estados Jogo::getEstado()
{
    return estado;
}
void Jogo::setEstado(Estados valor)
{
    estado = valor;
}
bool Jogo::getModo2Jogadores() const
{
    return modo2Jogadores;
}

Ente *Jogo::getCenarioAtual()
{
    if (estado >= MENU && estado <= RANKING_TELA)
        return pMenu;
    if (estado == FASE1)
        return pFase1;
    if (estado == FASE2)
        return pFase2;
    return NULL;
}

bool Jogo::temJogadoresCriados() const
{
    return (pJog1 != NULL);
}

std::string Jogo::getNomeJogador1() const
{
    return pJog1 ? pJog1->getNome() : "";
}

std::string Jogo::getNomeJogador2() const
{
    return pJog2 ? pJog2->getNome() : "";
}

Entidades::Personagens::Jogador *Jogo::getJogador2() const
{
    return pJog2;
}