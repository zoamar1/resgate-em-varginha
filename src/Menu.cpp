#include "Menu.hpp"

Menu::Menu() : Ente()
{
    pFig->setSize({LARGURA, ALTURA});
    pFig->setOrigin({0, 0});
    aplicarTextura(Gerenciadores::Menu);
};

Menu::~Menu()
{
}

void Menu::desenhaTexto()
{
    sf::Font fonte_titulo;
    fonte_titulo.loadFromFile("assets/fonts/AlfaSlabOne-Regular.ttf");
    sf::Text titulo("Resgate em Varginha", fonte_titulo, 60);
    titulo.setFillColor(sf::Color::Green);
    sf::FloatRect limitesTexto = titulo.getLocalBounds();
    titulo.setOrigin(limitesTexto.left + limitesTexto.width / 2.0f,
                     limitesTexto.top + limitesTexto.height / 2.0f);
    titulo.setPosition(LARGURA / 2, 200);
    pGG->desenhaTexto(titulo);
}

void Menu::executar()
{
    desenhar();
    desenhaTexto();
};