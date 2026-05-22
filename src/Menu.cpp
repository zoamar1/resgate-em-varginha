#include "Menu.hpp"

Menu::Menu() : Ente()
{
    pFig->setSize({LARGURA-1, ALTURA-1});
    pFig->setOrigin({0,0});
    pFig->setFillColor(sf::Color(255,0,0));
};

Menu::~Menu()
{
    
}

void Menu::executar()
{
    desenhar();
};