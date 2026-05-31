#include "Menu.hpp"

Menu::Menu() : Ente()
{
    pFig->setSize({LARGURA, ALTURA});
    pFig->setOrigin({0,0});
    aplicarTextura(Gerenciadores::Menu);
};

Menu::~Menu()
{
    
}

void Menu::executar()
{
    desenhar();
};