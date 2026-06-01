#pragma once
#include "Header.hpp"
#include "entidades/Ente.hpp"
#include <vector>
#include <string>

class Jogo;

class Menu : public Ente
{
    private:
        Jogo* pJogo;
        
        sf::Font fonte_padrao;
        sf::Text titulo;
        std::vector<sf::Text> opcoes_menu;

    private:
        void formataTexto(sf::Text& texto, const std::string& frase, int tamanho, float posY);

    public:
        Menu();
        ~Menu();
        void executar();
        void desenhaTexto();
};