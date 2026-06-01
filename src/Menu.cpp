#include "Menu.hpp"

Menu::Menu() : Ente()
{
    pFig->setSize({LARGURA, ALTURA});
    pFig->setOrigin({0, 0});
    aplicarTextura(Gerenciadores::Menu);

    if (!fonte_padrao.loadFromFile("assets/fonts/AlfaSlabOne-Regular.ttf")) {
        std::cout << "fonte deu erro" << std::endl;
    }

    formataTexto(titulo, "Resgate em Varginha", 60, 200.0f);
    titulo.setFillColor(sf::Color::Green);

    sf::Text opcao_jogar;
    formataTexto(opcao_jogar, "Jogar", 40, 400.0f);
    
    sf::Text opcao_sair;
    formataTexto(opcao_sair, "Sair", 40, 500.0f);

    opcoes_menu.push_back(opcao_jogar);
    opcoes_menu.push_back(opcao_sair);
};

Menu::~Menu()
{
}

void Menu::formataTexto(sf::Text& texto, const std::string& frase, int tamanho, float posY)
{
    texto.setFont(fonte_padrao);
    texto.setString(frase);
    texto.setCharacterSize(tamanho);
    texto.setFillColor(sf::Color::White);

    sf::FloatRect limites = texto.getLocalBounds();
    texto.setOrigin(limites.left + limites.width / 2.0f,
                    limites.top  + limites.height / 2.0f);
                     
    texto.setPosition(LARGURA / 2.0f, posY);
}

void Menu::desenhaTexto()
{
    pGG->desenhaTexto(titulo);

    for (int i = 0; i < opcoes_menu.size(); i++) {
        pGG->desenhaTexto(opcoes_menu[i]);
    }
}

void Menu::executar()
{
    desenhar();
    desenhaTexto();
};