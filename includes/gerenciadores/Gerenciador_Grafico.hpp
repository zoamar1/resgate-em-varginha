#pragma once
#include "Header.hpp"

class Ente;

namespace Gerenciadores
{
    enum IDTextura {
        Jogador,
        Guarda,
        Exercito,
        ET_Varginha,
        Plataforma,
        Projetil,
        Menu,
        Arbusto,
        Chao,
        FundoFase1,
        Espinhos
    };

    class Gerenciador_Grafico
    {
        private:
            static Gerenciador_Grafico* pGrafico;
            sf::RenderWindow window;
            std::vector<sf::Texture> texturas;
        private:
            Gerenciador_Grafico();
        public:
            static Gerenciador_Grafico* getGerenciador_Grafico();
            bool janelaAberta();
            sf::RenderWindow* getWindow();
            void fecharJanela();
            void desenhaRect(sf::RectangleShape rect);
            void desenhaTexto(sf::Text texto);
            void desenhaEnte(Ente* pE);
            void desenhaJanela();
            void limpaJanela();
            void carregaTexturas();
            sf::Texture& getTextura(IDTextura id);
    };
};