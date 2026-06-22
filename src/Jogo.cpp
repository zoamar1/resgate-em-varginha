#include "Jogo.hpp"

Jogo::Jogo()
    : pGG(Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()),
      pGE(Gerenciadores::Gerenciador_Eventos::getGerenciador_Eventos(this)),
      pGC(Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes()),
      estado(MENU),
      faseAoPausar(MENU),
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

void Jogo::iniciarFase1(const std::vector<std::string> &dadosCenario)
{
    if (pFase1)
    {
        delete pFase1;
        pFase1 = NULL;
    }
    if (pGC)
        pGC->limparColisoes();

    pFase1 = new Fases::FasePrimeira(pGC, dadosCenario);

    sf::Vector2f posJog1 = (dadosCenario.empty()) ? sf::Vector2f(100.0f, ALTURA - 100) : pJog1->getPosicao();
    pFase1->incluirJogador(pJog1, posJog1);
    if (pGC)
        pGC->incluirJogador(pJog1);

    if (modo2Jogadores && pJog2)
    {
        sf::Vector2f posJog2 = (dadosCenario.empty()) ? sf::Vector2f(200.0f, ALTURA - 100) : pJog2->getPosicao();
        pFase1->incluirJogador(pJog2, posJog2);
        if (pGC)
            pGC->incluirJogador(pJog2);
    }

    pFase1->vincularDonosProjeteis(pJog1, modo2Jogadores ? pJog2 : NULL);
}

void Jogo::iniciarFase2(const std::vector<std::string> &dadosCenario)
{
    if (pFase2)
    {
        delete pFase2;
        pFase2 = NULL;
    }
    if (pGC)
        pGC->limparColisoes();

    pFase2 = new Fases::FaseSegunda(pGC, dadosCenario);

    sf::Vector2f posJog1 = (dadosCenario.empty()) ? sf::Vector2f(100.0f, ALTURA - 100) : pJog1->getPosicao();
    pFase2->incluirJogador(pJog1, posJog1);
    if (pGC)
        pGC->incluirJogador(pJog1);

    if (modo2Jogadores && pJog2)
    {
        sf::Vector2f posJog2 = (dadosCenario.empty()) ? sf::Vector2f(200.0f, ALTURA - 100) : pJog2->getPosicao();
        pFase2->incluirJogador(pJog2, posJog2);
        if (pGC)
            pGC->incluirJogador(pJog2);
    }

    pFase2->vincularDonosProjeteis(pJog1, modo2Jogadores ? pJog2 : NULL);
}

void Jogo::salvarRanking()
{
    std::vector<std::pair<std::string, int>> novas;
    if (pJog1)
        novas.push_back({pJog1->getNome(), pJog1->getPontos()});
    if (modo2Jogadores && pJog2)
        novas.push_back({pJog2->getNome(), pJog2->getPontos()});
    Armazenamento::Ranking::salvar(novas);
}

void Jogo::salvarProgresso()
{
    int faseNum = (faseAoPausar == FASE2) ? 2 : 1;

    std::vector<std::string> dadosCenario;
    if (faseAoPausar == FASE1 && pFase1)
        dadosCenario = pFase1->coletarDadosSalvamento();
    else if (faseAoPausar == FASE2 && pFase2)
        dadosCenario = pFase2->coletarDadosSalvamento();

    Armazenamento::Salvamento::salvarJogo(pJog1, pJog2, modo2Jogadores, faseNum, dadosCenario);
}

void Jogo::carregarSalvamento(const std::string &chave)
{
    if (pGC) pGC->limparTudo();

    if (pJog1)
    {
        delete pJog1;
        pJog1 = NULL;
    }
    if (pJog2)
    {
        delete pJog2;
        pJog2 = NULL;
    }

    pJog1 = new Entidades::Personagens::Jogador(500, 0);
    pJog2 = new Entidades::Personagens::Jogador(500, 0);
    pJog1->setIndiceJogador(1);
    pJog2->setIndiceJogador(2);

    bool modo2 = false;
    int faseSalva = 1;
    std::vector<std::string> dadosCenario;

    bool ok = Armazenamento::Salvamento::carregarJogo(chave, pJog1, pJog2, modo2, faseSalva, dadosCenario);
    if (!ok)
    {
        delete pJog1;
        pJog1 = NULL;
        delete pJog2;
        pJog2 = NULL;
        return;
    }

    modo2Jogadores = modo2;

    if (!modo2Jogadores)
    {
        delete pJog2;
        pJog2 = NULL;
    }

    pGE->setJogador1(pJog1);
    pGE->setJogador2(modo2Jogadores ? pJog2 : NULL);

    if (faseSalva == 2)
    {
        estado = FASE2;
        iniciarFase2(dadosCenario);
    }
    else
    {
        estado = FASE1;
        iniciarFase1(dadosCenario);
    }
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

void Jogo::desenharMenuPausa()
{
    if (!pGG)
        return;

    sf::RectangleShape overlay(sf::Vector2f((float)LARGURA, (float)ALTURA));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    overlay.setPosition(0.0f, 0.0f);
    pGG->desenhaRect(overlay);

    if (!fontePlacarCarregada)
        return;

    sf::Text titulo;
    titulo.setFont(fontePlacar);
    titulo.setString("JOGO PAUSADO");
    titulo.setCharacterSize(70);
    titulo.setFillColor(sf::Color::White);
    sf::FloatRect r = titulo.getLocalBounds();
    titulo.setOrigin(r.left + r.width / 2.0f, r.top + r.height / 2.0f);
    titulo.setPosition(LARGURA / 2.0f, 350.0f);
    pGG->desenhaTexto(titulo);

    sf::Text op1;
    op1.setFont(fontePlacar);
    op1.setString("1 - Continuar Jogo");
    op1.setCharacterSize(45);
    op1.setFillColor(sf::Color::Yellow);
    sf::FloatRect r1 = op1.getLocalBounds();
    op1.setOrigin(r1.left + r1.width / 2.0f, r1.top + r1.height / 2.0f);
    op1.setPosition(LARGURA / 2.0f, 500.0f);
    pGG->desenhaTexto(op1);

    sf::Text op2;
    op2.setFont(fontePlacar);
    op2.setString("2 - Salvar e Voltar ao Menu");
    op2.setCharacterSize(45);
    op2.setFillColor(sf::Color::Yellow);
    sf::FloatRect r2 = op2.getLocalBounds();
    op2.setOrigin(r2.left + r2.width / 2.0f, r2.top + r2.height / 2.0f);
    op2.setPosition(LARGURA / 2.0f, 580.0f);
    pGG->desenhaTexto(op2);
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
            {
                pGG->fecharJanela();
                continue;
            }

            pGE->verificaTeclaPressionada(evento);
        }

        if (estado == FASE1 || estado == FASE2)
        {
            pGE->executar();
        }

        pGG->limpaJanela();
        Fases::Fase *faseDeletada = NULL;

        switch (estado)
        {
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

        case PAUSADO:
            if (faseAoPausar == FASE1 && pFase1)
                pFase1->desenharCena();
            else if (faseAoPausar == FASE2 && pFase2)
                pFase2->desenharCena();
            desenharPlacar();
            desenharMenuPausa();
            break;

        default:
            pMenu->executar();
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

Menu* Jogo::getMenu() const
{
    return pMenu;
}

void Jogo::setModo2Jogadores(bool modo)
{
    modo2Jogadores = modo;
}

void Jogo::limparJogadores()
{
    if (pJog2)
    {
        delete pJog2;
        pJog2 = NULL;
    }
}

void Jogo::configurarJogador1(const std::string& nome)
{
    if (pJog1)
    {
        if (pGC) pGC->limparTudo();
        delete pJog1;
        pJog1 = NULL;
    }
    pJog1 = new Entidades::Personagens::Jogador(500, 0);
    pJog1->setNome(nome);
    pJog1->setIndiceJogador(1);
    pGE->setJogador1(pJog1);
    
    if (!modo2Jogadores)
    {
        pGE->setJogador2(NULL);
    }
}

void Jogo::configurarJogador2(const std::string& nome)
{
    if (pJog2)
    {
        if (pGC) pGC->limparTudo();
        delete pJog2;
        pJog2 = NULL;
    }
    pJog2 = new Entidades::Personagens::Jogador(500, 0);
    pJog2->setNome(nome);
    pJog2->setIndiceJogador(2);
    pGE->setJogador2(pJog2);
}

void Jogo::deletarFases()
{
    if (faseAoPausar == FASE1 && pFase1)
    {
        delete pFase1;
        pFase1 = NULL;
    }
    else if (faseAoPausar == FASE2 && pFase2)
    {
        delete pFase2;
        pFase2 = NULL;
    }
}

void Jogo::pausarJogo()
{
    if (estado == FASE1 || estado == FASE2)
    {
        faseAoPausar = estado;
        estado = PAUSADO;
    }
}

void Jogo::despausarJogo()
{
    if (estado == PAUSADO)
    {
        estado = faseAoPausar;
    }
}