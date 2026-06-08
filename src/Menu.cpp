#include "Menu.hpp"

Menu::Menu() : Ente()
{
    pFig->setSize({LARGURA, ALTURA});
    pFig->setOrigin({0, 0});
    aplicarTextura(Gerenciadores::Menu);

    if (!fonte_padrao.loadFromFile("assets/fonts/AlfaSlabOne-Regular.ttf"))
    {
        std::cout << "fonte deu erro" << std::endl;
    }

    formataTexto(titulo, "Resgate em Varginha", 80, 250.0f);
    titulo.setFillColor(sf::Color::Blue);

    formataTexto(opcao_fase1, "1 - Fase 1", 40, 600.0f);

    formataTexto(opcao_fase2, "2 - Fase 2", 40, 675.0f);

    formataTexto(opcao_sair, "Sair (ESC)", 40, 750.0f);

    opcoes_menu.push_back(opcao_fase1);
    opcoes_menu.push_back(opcao_fase2);
    opcoes_menu.push_back(opcao_sair);
};

Menu::~Menu()
{
}

void Menu::formataTexto(sf::Text &texto, const std::string &frase, int tamanho, float posY)
{
    texto.setFont(fonte_padrao);
    texto.setString(frase);
    texto.setCharacterSize(tamanho);
    texto.setFillColor(sf::Color::White);

    sf::FloatRect limites = texto.getLocalBounds();
    texto.setOrigin(limites.left + limites.width / 2.0f,
                    limites.top + limites.height / 2.0f);

    texto.setPosition(LARGURA / 2.0f, posY);
}

void Menu::desenhaTexto()
{
    pGG->desenhaTexto(titulo);

    for (int i = 0; i < (int)opcoes_menu.size(); i++)
    {
        pGG->desenhaTexto(opcoes_menu[i]);
    }
}

void Menu::executar()
{
    desenhar();
    desenhaTexto();
};