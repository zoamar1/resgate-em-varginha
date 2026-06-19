#include "Menu.hpp"
#include "Jogo.hpp"


Menu::Menu() : Ente(), pJogo(NULL), telaAtual(TelaMenu::PRINCIPAL), indice_cadastro(1)
{
    pFig->setSize({LARGURA, ALTURA});
    pFig->setOrigin({0, 0});
    aplicarTextura(Gerenciadores::Menu);

    if (!fonte_padrao.loadFromFile("assets/fonts/AlfaSlabOne-Regular.ttf"))
        std::cout << "Erro ao carregar fonte do menu." << std::endl;

    formataTexto(titulo, "Resgate em Varginha", 80, 180.0f, sf::Color::Blue);
    formataTexto(opcao_ranking, "3 - Ver Ranking", 40, 580.0f);
    formataTexto(opcao_sair, "Sair (ESC)", 40, 660.0f);
    formataTexto(texto_prompt, "Digite seu nome:", 50, 400.0f);
    formataTexto(texto_input, "", 60, 500.0f, sf::Color::Yellow);
}

Menu::~Menu() {}

void Menu::formataTexto(sf::Text &texto, const std::string &frase, int tamanho, float posY, sf::Color cor)
{
    texto.setFont(fonte_padrao);
    texto.setString(frase);
    texto.setCharacterSize(tamanho);
    texto.setFillColor(cor);

    sf::FloatRect limites = texto.getLocalBounds();
    texto.setOrigin(limites.left + limites.width / 2.0f, limites.top + limites.height / 2.0f);
    texto.setPosition(LARGURA / 2.0f, posY);
}

void Menu::iniciarCadastro(int indice)
{
    indice_cadastro = indice;
    buffer_nome.clear();

    std::string prompt = (indice == 1) ? "Nome do Jogador 1:" : "Nome do Jogador 2:";
    formataTexto(texto_prompt, prompt, 50, 380.0f);
    formataTexto(texto_input, "_", 60, 480.0f, sf::Color::Yellow);
    telaAtual = TelaMenu::CADASTRO_NOME;
}

void Menu::processarEventoTexto(sf::Uint32 unicode)
{
    if (telaAtual != TelaMenu::CADASTRO_NOME)
        return;
    if (unicode >= 32 && unicode < 127 && buffer_nome.size() < 16)
    {
        buffer_nome += static_cast<char>(unicode);
        formataTexto(texto_input, buffer_nome + "_", 60, 480.0f, sf::Color::Yellow);
    }
}

void Menu::apagarUltimoChar()
{
    if (!buffer_nome.empty())
    {
        buffer_nome.pop_back();
        formataTexto(texto_input, buffer_nome + "_", 60, 480.0f, sf::Color::Yellow);
    }
}

void Menu::confirmarNome()
{
    if (buffer_nome.empty())
        buffer_nome = (indice_cadastro == 1) ? "Jogador1" : "Jogador2";
}

const std::string &Menu::getNomeDigitado() const
{
    return buffer_nome;
}

void Menu::atualizaRanking()
{
    textos_ranking.clear();

    sf::Text tituloR;
    formataTexto(tituloR, "-- RANKING --", 60, 100.0f, sf::Color::Yellow);
    textos_ranking.push_back(tituloR);

    std::vector<std::pair<std::string, int>> entradas = Ranking::carregar();
    int limite = (entradas.size() < 10) ? (int)entradas.size() : 10;

    for (int i = 0; i < limite; i++)
    {
        std::ostringstream ss;
        ss << (i + 1) << ". " << entradas[i].first << "  -  " << entradas[i].second << " pts";
        sf::Text linha;
        formataTexto(linha, ss.str(), 36, 200.0f + i * 65.0f);
        textos_ranking.push_back(linha);
    }

    if (limite == 0)
    {
        sf::Text vazio;
        formataTexto(vazio, "Nenhuma partida salva ainda.", 36, 300.0f, sf::Color(180, 180, 180));
        textos_ranking.push_back(vazio);
    }

    sf::Text voltar;
    formataTexto(voltar, "Pressione ESC para voltar", 30, 900.0f, sf::Color(200, 200, 200));
    textos_ranking.push_back(voltar);
}

void Menu::setJogo(Jogo *pJ)
{
    pJogo = pJ;
}

void Menu::desenhaTextoPrincipal()
{
    formataTexto(titulo, "Resgate em Varginha", 80, 180.0f, sf::Color::Blue);
    pGG->desenhaTexto(titulo);

    formataTexto(opcao_1jog, "1 - Continuar Jogo", 40, 420.0f);
    formataTexto(opcao_2jog, "2 - Criar Jogo (Novo)", 40, 500.0f);

    pGG->desenhaTexto(opcao_1jog);
    pGG->desenhaTexto(opcao_2jog);
    pGG->desenhaTexto(opcao_ranking);
    pGG->desenhaTexto(opcao_sair);
}

void Menu::desenhaSelecaoModo()
{
    formataTexto(titulo, "Modo de Jogo", 70, 180.0f, sf::Color::Cyan);
    pGG->desenhaTexto(titulo);

    formataTexto(opcao_1jog, "1 - Solo (1 Jogador)", 40, 420.0f);
    formataTexto(opcao_2jog, "2 - Dupla (2 Jogadores)", 40, 500.0f);

    pGG->desenhaTexto(opcao_1jog);
    pGG->desenhaTexto(opcao_2jog);

    sf::Text voltar;
    formataTexto(voltar, "Pressione ESC para voltar", 30, 850.0f, sf::Color(200, 200, 200));
    pGG->desenhaTexto(voltar);
}

void Menu::desenhaContinuarJogo()
{
    formataTexto(titulo, "Continuar Partida", 70, 150.0f, sf::Color::Green);
    pGG->desenhaTexto(titulo);

    for (size_t i = 0; i < textos_continuar.size(); i++)
        pGG->desenhaTexto(textos_continuar[i]);
}

void Menu::desenhaSelecaoFase()
{
    formataTexto(titulo, "Escolha a Fase", 70, 180.0f, sf::Color::Magenta);
    pGG->desenhaTexto(titulo);

    formataTexto(opcao_1jog, "1 - Primeira Fase", 40, 420.0f);
    formataTexto(opcao_2jog, "2 - Segunda Fase", 40, 500.0f);

    pGG->desenhaTexto(opcao_1jog);
    pGG->desenhaTexto(opcao_2jog);

    sf::Text voltar;
    formataTexto(voltar, "Pressione ESC para voltar", 30, 850.0f, sf::Color(200, 200, 200));
    pGG->desenhaTexto(voltar);
}

void Menu::desenhaRanking()
{
    for (size_t i = 0; i < textos_ranking.size(); i++)
        pGG->desenhaTexto(textos_ranking[i]);
}

void Menu::desenhaCadastro()
{
    pGG->desenhaTexto(texto_prompt);
    pGG->desenhaTexto(texto_input);
}

void Menu::desenhaTexto()
{
    switch (telaAtual)
    {
    case TelaMenu::PRINCIPAL:
        desenhaTextoPrincipal();
        break;
    case TelaMenu::SELECAO_MODO:
        desenhaSelecaoModo();
        break;
    case TelaMenu::CONTINUAR_JOGO:
        desenhaContinuarJogo();
        break;
    case TelaMenu::SELECAO_FASE:
        desenhaSelecaoFase();
        break;
    case TelaMenu::RANKING:
        desenhaRanking();
        break;
    case TelaMenu::CADASTRO_NOME:
        desenhaCadastro();
        break;
    }
}

void Menu::executar()
{
    desenhar();
    desenhaTexto();
}

void Menu::setTela(TelaMenu t)
{
    telaAtual = t;
    if (t == TelaMenu::RANKING)
        atualizaRanking();
    else if (t == TelaMenu::CONTINUAR_JOGO)
        atualizaListaSalvamentos();
}

TelaMenu Menu::getTela() const
{
    return telaAtual;
}

void Menu::atualizaListaSalvamentos()
{
    textos_continuar.clear();
    chavesSalvamento.clear();

    sf::Text tituloR;
    formataTexto(tituloR, "Escolha o jogo salvo", 50, 250.0f, sf::Color::Yellow);
    textos_continuar.push_back(tituloR);

    std::vector<std::pair<std::string, std::string>> resumos = Salvamento::listarResumos();
    int limite = (resumos.size() < 9) ? (int)resumos.size() : 9;

    for (int i = 0; i < limite; i++)
    {
        chavesSalvamento.push_back(resumos[i].first);
        std::ostringstream ss;
        ss << (i + 1) << " - " << resumos[i].second;
        sf::Text linha;
        formataTexto(linha, ss.str(), 32, 350.0f + i * 55.0f);
        textos_continuar.push_back(linha);
    }

    if (resumos.empty())
    {
        sf::Text vazio;
        formataTexto(vazio, "Nenhum jogo salvo encontrado.", 36, 400.0f, sf::Color(180, 180, 180));
        textos_continuar.push_back(vazio);
    }

    sf::Text voltar;
    formataTexto(voltar, "Pressione ESC para voltar", 30, 900.0f, sf::Color(200, 200, 200));
    textos_continuar.push_back(voltar);
}

const std::vector<std::string> &Menu::getChavesSalvamento() const
{
    return chavesSalvamento;
}